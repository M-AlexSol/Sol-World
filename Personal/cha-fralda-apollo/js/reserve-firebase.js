/*
// Reserva compartilhada via Firebase Firestore + Auth (anônimo).
// IMPORTANTE: Não coloque chaves sensíveis no repositório. Use injeção em runtime.

import { initializeApp } from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-app.js';
import { getAuth, signInAnonymously, onAuthStateChanged } from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-auth.js';
import {
    getFirestore,
    doc,
    getDoc,
    setDoc,
    runTransaction,
    onSnapshot,
    serverTimestamp
} from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-firestore.js';

// Carrega a config a partir de uma variável inserida no deploy (window.__FIREBASE_CONFIG__).
// Se não existir, usamos um fallback não-sensível para evitar expor chaves no repo.
const FIREBASE_CONFIG = window.__FIREBASE_CONFIG__ || {
    apiKey: "REDACTED_IN_REPO",
    authDomain: "cha-apollo.firebaseapp.com",
    projectId: "cha-apollo",
    storageBucket: "cha-apollo.firebasestorage.app",
    messagingSenderId: "518245508761",
    appId: "1:518245508761:web:16ac54df5b029f3f377a08",
    measurementId: "G-LCMF92SBC8"
};

const app = initializeApp(FIREBASE_CONFIG);
const auth = getAuth(app);
const db = getFirestore(app);

let currentUid = null;

// DEBUG: mostrar estado inicial
console.log('[reserve-firebase] Iniciando módulo reserve-firebase.js');

// sign in anon
async function ensureAnonymousAuth() {
    return new Promise((resolve, reject) => {
        onAuthStateChanged(auth, (user) => {
            if (user) {
                currentUid = user.uid;
                console.log('[reserve-firebase] Auth state changed - uid:', currentUid);
                resolve(user);
            } else {
                signInAnonymously(auth).catch(reject);
            }
        });
    });
}

function docIdFromUrl(url) {
    // doc IDs cannot contain some chars; encodeURIComponent é suficiente
    return encodeURIComponent(url);
}

function renderReservedUIRemote(row, data) {
    // data: { reserved: true, uid, name, ts }
    const buyArea = row.querySelector('.buy-area');
    if (!buyArea) return;
    buyArea.innerHTML = '';

    const badge = document.createElement('span');
    badge.className = 'reserved-badge';
    const name = data.name || '';
    const text = document.createElement('span');
    text.textContent = name ? 'Reservado por:' : 'Reservado';
    const nameSpan = document.createElement('span');
    nameSpan.className = 'reserved-name';
    nameSpan.textContent = name ? (' ' + name) : ' com carinho';
    badge.appendChild(text);
    badge.appendChild(nameSpan);

    // Se o usuário que reservou é o mesmo do cliente atual, mostramos "Cancelar reserva"
    if (data.uid && currentUid && data.uid === currentUid) {
        const undo = document.createElement('button');
        undo.className = 'unreserve-link';
        undo.type = 'button';
        undo.textContent = 'Cancelar reserva';
        undo.addEventListener('click', async () => {
            const docRef = doc(db, 'reservas', docIdFromUrl(row.dataset.url));
            try {
                // permitir apenas o dono remover (transaction)
                await runTransaction(db, async (tx) => {
                    const snap = await tx.get(docRef);
                    if (!snap.exists()) return;
                    const payload = snap.data();
                    if (payload.uid !== currentUid) throw new Error('Sem permissão');
                    tx.delete(docRef);
                });
                // UI será atualizada pelo listener onSnapshot
            } catch (err) {
                console.error('Não foi possível cancelar:', err);
                alert('Não foi possível cancelar a reserva.');
            }
        });
        buyArea.appendChild(badge);
        buyArea.appendChild(undo);
    } else {
        buyArea.appendChild(badge);
    }
    row.classList.add('reserved');
    row.setAttribute('aria-disabled', 'true');
}

function buildBuyAreaLocal(row) {
    const url = row.dataset.url;
    const buyArea = row.querySelector('.buy-area');
    if (!buyArea) return;
    buyArea.innerHTML = '';

    const buyAnchor = document.createElement('a');
    buyAnchor.className = 'choice-button buy-button';
    buyAnchor.href = url || '#';
    buyAnchor.target = '_blank';
    buyAnchor.rel = 'noopener noreferrer';
    buyAnchor.textContent = 'Abrir na Loja';

    const reserveBtn = document.createElement('button');
    reserveBtn.className = 'reserve-button';
    reserveBtn.type = 'button';
    reserveBtn.textContent = 'Reservar';

    buyArea.appendChild(buyAnchor);
    buyArea.appendChild(reserveBtn);

    reserveBtn.addEventListener('click', async (ev) => {
        ev.preventDefault();
        console.log('[reserve-firebase] Reservar clicado — url=', url, ' currentUid=', currentUid);
        // pedir confirmação e nome (simples prompt para manter código curto)
        const name = prompt('Tem certeza? (Opcional) Digite seu nome para aparecer na reserva.\nDeixe vazio para "Reservado com carinho".', '') || '';
        if (name === null) return; // cancel
        const docRef = doc(db, 'reservas', docIdFromUrl(url));
        try {
            await runTransaction(db, async (tx) => {
                const snap = await tx.get(docRef);
                if (snap.exists()) {
                    throw new Error('Já reservado');
                }
                tx.set(docRef, {
                    reserved: true,
                    uid: currentUid || null,
                    name: name || '',
                    ts: serverTimestamp()
                });
            });
            // listener onSnapshot atualizará a UI
        } catch (err) {
            console.error('[reserve-firebase] Erro ao reservar (detalhe):', err);
            // mostra o erro real para debug, depois exibe mensagem mais legível ao usuário
            const msg = err && err.message ? err.message : String(err);
            alert('Não foi possível reservar: ' + msg);
        }
    });
}

// inicializar listeners por item
async function initListeners() {
    // garantir auth
    await ensureAnonymousAuth();

    const rows = Array.from(document.querySelectorAll('.item-row'));
    for (const row of rows) {
        const url = row.dataset.url;
        if (!url) {
            // rebuild local buy area if needed
            buildBuyAreaLocal(row);
            continue;
        }
        const docRef = doc(db, 'reservas', docIdFromUrl(url));
        // listener em tempo real
        onSnapshot(docRef, (snap) => {
            if (snap.exists()) {
                const data = snap.data();
                renderReservedUIRemote(row, data);
            } else {
                // se não existe doc -> reconstruir buy area (botão comprar + reservar)
                // remover reserved visual
                row.classList.remove('reserved');
                row.removeAttribute('aria-disabled');
                buildBuyAreaLocal(row);
            }
        }, (err) => {
            console.error('snapshot err', err);
            // fallback: show local buy area
            buildBuyAreaLocal(row);
        });
    }
}

// start
initListeners().catch((err) => {
    console.error('[reserve-firebase] Init Firebase reserve failed', err);
    document.querySelectorAll('.item-row').forEach(buildBuyAreaLocal);
});
*/


// Reserva compartilhada via Firebase Firestore + Auth (anônimo).
// IMPORTANTE: Não coloque chaves sensíveis no repositório. Use injeção em runtime.

import { initializeApp } from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-app.js';
import { getAuth, signInAnonymously, onAuthStateChanged } from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-auth.js';
import {
  getFirestore,
  doc,
  getDoc,
  setDoc,
  runTransaction,
  onSnapshot,
  serverTimestamp
} from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-firestore.js';

// ---------- RUNTIME CONFIG / INIT GUARD ----------
// Carrega a config a partir de window.__FIREBASE_CONFIG__ (injetado via config.js no deploy).
// Se não existir ou for inválido, usamos fallback local sem tentar inicializar o SDK Firebase.
const RUNTIME_CONFIG = window.__FIREBASE_CONFIG__ || null;

let app = null;
let auth = null;
let db = null;
let USE_FIREBASE = false;

if (RUNTIME_CONFIG && RUNTIME_CONFIG.apiKey) {
  try {
    app = initializeApp(RUNTIME_CONFIG);
    auth = getAuth(app);
    db = getFirestore(app);
    USE_FIREBASE = true;
    console.log('[reserve-firebase] Firebase inicializado (modo compartilhado).');
  } catch (e) {
    console.error('[reserve-firebase] Falha ao inicializar Firebase, caindo para fallback local:', e);
    USE_FIREBASE = false;
  }
} else {
  console.warn('[reserve-firebase] Nenhuma configuração Firebase detectada (window.__FIREBASE_CONFIG__). Usando fallback local.');
}

// ---------- Local fallback storage (usado quando USE_FIREBASE === false) ----------
const LOCAL_STORAGE_KEY = 'apollo:reserved_local_v1';
let localReserved = {};

function loadLocalReserved() {
  try {
    localReserved = JSON.parse(localStorage.getItem(LOCAL_STORAGE_KEY) || '{}');
  } catch (e) {
    localReserved = {};
  }
}
function saveLocalReserved() {
  try {
    localStorage.setItem(LOCAL_STORAGE_KEY, JSON.stringify(localReserved));
  } catch (e) { /* ignore */ }
}

// ---------- Shared state ----------
let currentUid = null;

// DEBUG: mostrar estado inicial
console.log('[reserve-firebase] Iniciando módulo reserve-firebase.js - USE_FIREBASE=', USE_FIREBASE);

// ---------- Auth helper (no-Firebase returns resolved promise) ----------
async function ensureAnonymousAuth() {
  if (!USE_FIREBASE) {
    // nothing to do in local mode
    return Promise.resolve(null);
  }
  return new Promise((resolve, reject) => {
    onAuthStateChanged(auth, (user) => {
      if (user) {
        currentUid = user.uid;
        console.log('[reserve-firebase] Auth state changed - uid:', currentUid);
        resolve(user);
      } else {
        signInAnonymously(auth).catch((err) => {
          console.error('[reserve-firebase] signInAnonymously failed', err);
          reject(err);
        });
      }
    });
  });
}

// ---------- util ----------
function docIdFromUrl(url) {
  return encodeURIComponent(url);
}

// ---------- UI renderers ----------

function renderReservedUIRemote(row, data) {
  // data: { reserved: true, uid, name, ts }
  const buyArea = row.querySelector('.buy-area');
  if (!buyArea) return;
  buyArea.innerHTML = '';

  const badge = document.createElement('span');
  badge.className = 'reserved-badge';
  const name = data.name || '';
  const text = document.createElement('span');
  text.textContent = name ? 'Reservado por:' : 'Reservado';
  const nameSpan = document.createElement('span');
  nameSpan.className = 'reserved-name';
  nameSpan.textContent = name ? (' ' + name) : ' com carinho';
  badge.appendChild(text);
  badge.appendChild(nameSpan);

  // Se o usuário que reservou é o mesmo do cliente atual, mostramos "Cancelar reserva"
  if (data.uid && currentUid && data.uid === currentUid) {
    const undo = document.createElement('button');
    undo.className = 'unreserve-link';
    undo.type = 'button';
    undo.textContent = 'Cancelar reserva';
    undo.addEventListener('click', async () => {
      const docRef = doc(db, 'reservas', docIdFromUrl(row.dataset.url));
      try {
        await runTransaction(db, async (tx) => {
          const snap = await tx.get(docRef);
          if (!snap.exists()) return;
          const payload = snap.data();
          if (payload.uid !== currentUid) throw new Error('Sem permissão');
          tx.delete(docRef);
        });
        // UI será atualizada pelo listener onSnapshot
      } catch (err) {
        console.error('[reserve-firebase] Não foi possível cancelar:', err);
        alert('Não foi possível cancelar a reserva.');
      }
    });
    buyArea.appendChild(badge);
    buyArea.appendChild(undo);
  } else {
    buyArea.appendChild(badge);
  }
  row.classList.add('reserved');
  row.setAttribute('aria-disabled', 'true');
}

function renderReservedUILocal(row, url) {
  const buyArea = row.querySelector('.buy-area');
  if (!buyArea) return;
  buyArea.innerHTML = '';
  const meta = localReserved[url] || {};
  const name = meta.name || '';
  const badge = document.createElement('span');
  badge.className = 'reserved-badge';
  const text = document.createElement('span');
  text.textContent = name ? 'Reservado por:' : 'Reservado';
  const nameSpan = document.createElement('span');
  nameSpan.className = 'reserved-name';
  nameSpan.textContent = name ? (' ' + name) : ' com carinho';
  badge.appendChild(text);
  badge.appendChild(nameSpan);

  const undo = document.createElement('button');
  undo.className = 'unreserve-link';
  undo.type = 'button';
  undo.textContent = 'Cancelar reserva';
  undo.addEventListener('click', () => {
    delete localReserved[url];
    saveLocalReserved();
    initRow(row);
  });

  buyArea.appendChild(badge);
  buyArea.appendChild(undo);
  row.classList.add('reserved');
  row.setAttribute('aria-disabled', 'true');
}

// ---------- Build buy area: branch behavior by USE_FIREBASE ----------
function buildBuyAreaLocal(row) {
  const url = row.dataset.url;
  const buyArea = row.querySelector('.buy-area');
  if (!buyArea) return;
  buyArea.innerHTML = '';

  const buyAnchor = document.createElement('a');
  buyAnchor.className = 'choice-button buy-button';
  buyAnchor.href = url || '#';
  buyAnchor.target = '_blank';
  buyAnchor.rel = 'noopener noreferrer';
  buyAnchor.textContent = 'Abrir na Loja';

  const reserveBtn = document.createElement('button');
  reserveBtn.className = 'reserve-button';
  reserveBtn.type = 'button';
  reserveBtn.textContent = 'Reservar';

  buyArea.appendChild(buyAnchor);
  buyArea.appendChild(reserveBtn);

  reserveBtn.addEventListener('click', async (ev) => {
    ev.preventDefault();
    console.log('[reserve-firebase] Reservar clicado — url=', url, ' currentUid=', currentUid, ' USE_FIREBASE=', USE_FIREBASE);
    // prompt de confirmação + nome
    const name = prompt('Tem certeza? (Opcional) Digite seu nome para aparecer na reserva.\nDeixe vazio para "Reservado com carinho".', '') || '';
    if (name === null) return; // cancel

    if (USE_FIREBASE) {
      // Firebase path: use transaction to prevent double-reserve
      const docRef = doc(db, 'reservas', docIdFromUrl(url));
      try {
        await runTransaction(db, async (tx) => {
          const snap = await tx.get(docRef);
          if (snap.exists()) {
            throw new Error('Já reservado');
          }
          tx.set(docRef, {
            reserved: true,
            uid: currentUid || null,
            name: name || '',
            ts: serverTimestamp()
          });
        });
        // UI será atualizada pelo listener onSnapshot
      } catch (err) {
        console.error('[reserve-firebase] Erro ao reservar (detalhe):', err);
        const msg = err && err.message ? err.message : String(err);
        alert('Não foi possível reservar: ' + msg);
      }
    } else {
      // Local fallback: save in localStorage
      if (!url) return;
      loadLocalReserved();
      localReserved[url] = { ts: Date.now(), by: 'local', name: name || '' };
      saveLocalReserved();
      renderReservedUILocal(row, url);
    }
  });
}

// ---------- helper to initialize a single row (used in local fallback) ----------
function initRow(row) {
  const url = row.dataset.url;
  row.classList.remove('reserved');
  row.removeAttribute('aria-disabled');

  if (!USE_FIREBASE) {
    loadLocalReserved();
    if (url && localReserved[url]) {
      renderReservedUILocal(row, url);
      return;
    }
    buildBuyAreaLocal(row);
    return;
  }

  // If using Firebase mode, buildBuyAreaLocal will set firebase reservation behavior
  buildBuyAreaLocal(row);
}

// ---------- init listeners for Firebase mode or fallback ----------

async function initListeners() {
  if (!USE_FIREBASE) {
    // fallback local: initialize rows from localStorage
    loadLocalReserved();
    document.querySelectorAll('.item-row').forEach(initRow);

    // observe dyn additions
    const main = document.querySelector('main') || document.body;
    const observer = new MutationObserver((mutations) => {
      for (const m of mutations) {
        for (const node of m.addedNodes) {
          if (!(node instanceof HTMLElement)) continue;
          if (node.matches && node.matches('.item-row')) initRow(node);
          node.querySelectorAll && node.querySelectorAll('.item-row').forEach(initRow);
        }
      }
    });
    observer.observe(main, { childList: true, subtree: true });
    return;
  }

  // Firebase mode:
  await ensureAnonymousAuth();

  const rows = Array.from(document.querySelectorAll('.item-row'));
  for (const row of rows) {
    const url = row.dataset.url;
    if (!url) {
      buildBuyAreaLocal(row);
      continue;
    }
    const docRef = doc(db, 'reservas', docIdFromUrl(url));
    // listener em tempo real
    onSnapshot(docRef, (snap) => {
      if (snap.exists()) {
        const data = snap.data();
        renderReservedUIRemote(row, data);
      } else {
        // se não existe doc -> reconstruir buy area (botão comprar + reservar)
        row.classList.remove('reserved');
        row.removeAttribute('aria-disabled');
        buildBuyAreaLocal(row);
      }
    }, (err) => {
      console.error('[reserve-firebase] snapshot err', err);
      // fallback: show local buy area
      buildBuyAreaLocal(row);
    });
  }

  // observe dyn additions: attach listener/initialization
  const main = document.querySelector('main') || document.body;
  const observer = new MutationObserver((mutations) => {
    for (const m of mutations) {
      for (const node of m.addedNodes) {
        if (!(node instanceof HTMLElement)) continue;
        node.querySelectorAll && node.querySelectorAll('.item-row').forEach((r) => {
          // attach snapshot for new rows
          const url = r.dataset.url;
          if (!url) {
            initRow(r);
            return;
          }
          const docRef = doc(db, 'reservas', docIdFromUrl(url));
          onSnapshot(docRef, (snap) => {
            if (snap.exists()) renderReservedUIRemote(r, snap.data());
            else initRow(r);
          }, (err) => {
            console.error('[reserve-firebase] snapshot err (dynamic)', err);
            initRow(r);
          });
        });
      }
    }
  });
  observer.observe(main, { childList: true, subtree: true });
}

// ---------- start ----------

if (!USE_FIREBASE) {
  console.log('[reserve-firebase] Executando fallback local (sem Firestore).');
  // initialize local UI
  initListeners().catch((err) => {
    console.error('[reserve-firebase] Fallback init failed', err);
  });
} else {
  initListeners().catch((err) => {
    console.error('[reserve-firebase] Init Firebase reserve failed', err);
    // fallback: rebuild local UI without real-time
    document.querySelectorAll('.item-row').forEach(initRow);
  });
}