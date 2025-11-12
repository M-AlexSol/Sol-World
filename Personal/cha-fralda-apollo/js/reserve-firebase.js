// Reserva compartilhada via Firebase Firestore + Auth (anônimo).
// NÃO coloque chaves sensíveis no repositório. Use injeção em runtime via config.js.

import { initializeApp } from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-app.js';
import { getAuth, signInAnonymously, onAuthStateChanged } from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-auth.js';
import {
    getFirestore,
    doc,
    getDoc,
    runTransaction,
    onSnapshot,
    serverTimestamp
} from 'https://www.gstatic.com/firebasejs/9.22.1/firebase-firestore.js';

// ---------- RUNTIME CONFIG / INIT GUARD ----------
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
        console.log('[reserve-firebase] Firebase inicializado (modo compartilhado). RUNTIME_CONFIG.projectId=', RUNTIME_CONFIG.projectId);
    } catch (e) {
        console.error('[reserve-firebase] Falha ao inicializar Firebase, caindo para fallback local:', e);
        USE_FIREBASE = false;
    }
} else {
    console.warn('[reserve-firebase] Nenhuma configuração Firebase detectada (window.__FIREBASE_CONFIG__). Usando fallback local.');
}

// ---------- Local fallback storage ----------
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

console.log('[reserve-firebase] Iniciando módulo reserve-firebase.js - USE_FIREBASE=', USE_FIREBASE);

// ---------- Auth helper ----------
async function ensureAnonymousAuth() {
    if (!USE_FIREBASE) return Promise.resolve(null);
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

// ---------- UI renderers (multi-quantidade) ----------
function renderReservedUIRemote(row, data) {
    // data: { max, holders: [{ uid, name, qty, ts }], reservedTotal }
    const buyArea = row.querySelector('.buy-area');
    if (!buyArea) return;
    buyArea.innerHTML = '';

    const holders = Array.isArray(data.holders) ? data.holders : [];
    const reservedTotal = typeof data.reservedTotal === 'number'
        ? data.reservedTotal
        : holders.reduce((s, h) => s + (h.qty || 0), 0);
    const max = (typeof data.max === 'number') ? data.max : (parseInt(row.dataset.max, 10) || 1);
    const remaining = Math.max(0, max - reservedTotal);

    const badge = document.createElement('span');
    badge.className = 'reserved-badge';

    if (holders.length === 0) {
        const text = document.createElement('span');
        text.textContent = 'Reservado';
        badge.appendChild(text);
    } else {
        const text = document.createElement('span');
        text.textContent = 'Reservado por: ';
        badge.appendChild(text);

        const list = document.createElement('span');
        list.className = 'reserved-list';
        const parts = holders.map(h => {
            const name = (h.name && h.name.trim()) ? h.name.trim() : (h.uid ? 'Convidado' : 'Reservado');
            return `${name} (${h.qty || 1})`;
        });
        list.textContent = parts.join(', ');
        badge.appendChild(list);
    }

    buyArea.appendChild(badge);

    // Show "Cancelar minha reserva" if currentUid is among holders
    const myHolder = holders.find(h => h.uid && currentUid && h.uid === currentUid);
    if (myHolder) {
        const undo = document.createElement('button');
        undo.className = 'unreserve-link';
        undo.type = 'button';
        undo.textContent = 'Cancelar minha reserva';
        undo.addEventListener('click', async () => {
            const docRef = doc(db, 'reservas', docIdFromUrl(row.dataset.url));
            try {
                await runTransaction(db, async (tx) => {
                    const snap = await tx.get(docRef);
                    if (!snap.exists()) return;
                    const cur = snap.data() || {};
                    const curHolders = Array.isArray(cur.holders) ? cur.holders.slice() : [];
                    const newHolders = curHolders.filter(h => !(h.uid && h.uid === currentUid));
                    const newTotal = newHolders.reduce((s, h) => s + (h.qty || 0), 0);
                    if (newHolders.length === 0) {
                        tx.delete(docRef);
                    } else {
                        tx.set(docRef, {
                            max: cur.max || max,
                            holders: newHolders,
                            reservedTotal: newTotal,
                            updatedAt: serverTimestamp()
                        });
                    }
                });
                // UI atualizada pelo onSnapshot listener
            } catch (err) {
                console.error('[reserve-firebase] Não foi possível cancelar (detalhe):', err);
                alert('Não foi possível cancelar a reserva.');
            }
        });
        buyArea.appendChild(undo);
    } else {
        // If user is not a holder and there's remaining units, show Reserve button + shop link
        if (remaining > 0) {
            // create shop link
            const buyAnchor = document.createElement('a');
            buyAnchor.className = 'choice-button buy-button';
            buyAnchor.href = row.dataset.url || '#';
            buyAnchor.target = '_blank';
            buyAnchor.rel = 'noopener noreferrer';
            buyAnchor.textContent = 'Abrir na Loja';
            buyArea.appendChild(buyAnchor);

            // create reserve button
            const reserveBtn = document.createElement('button');
            reserveBtn.className = 'reserve-button';
            reserveBtn.type = 'button';
            reserveBtn.textContent = `Reservar (${remaining} disponíveis)`;
            reserveBtn.addEventListener('click', async (ev) => {
                ev.preventDefault();
                const url = row.dataset.url;
                const declaredMax = row.dataset.max ? parseInt(row.dataset.max, 10) : 1;
                const name = prompt('Tem certeza? (Opcional) Digite seu nome para aparecer na reserva.\nDeixe vazio para "Reservado com carinho".', '') || '';
                if (name === null) return;

                try {
                    const docRef = doc(db, 'reservas', docIdFromUrl(url));
                    // re-check and transact
                    await runTransaction(db, async (tx) => {
                        const s = await tx.get(docRef);
                        const base = s.exists() ? (s.data() || {}) : {};
                        const curMax = (typeof base.max === 'number') ? base.max : declaredMax || 1;
                        const curHolders = Array.isArray(base.holders) ? base.holders.slice() : [];
                        const curTotal = curHolders.reduce((ss, h) => ss + (h.qty || 0), 0);
                        const curRemaining = Math.max(0, curMax - curTotal);
                        if (curRemaining <= 0) throw new Error('Desculpe — não há mais unidades disponíveis desse item.');

                        let qtyStr = prompt(`Quantos desse item você quer reservar? Disponíveis: ${curRemaining}`, '1');
                        if (qtyStr === null) return;
                        const qty = Math.max(0, parseInt(qtyStr, 10) || 0);
                        if (!qty || qty < 1 || qty > curRemaining) { throw new Error('Quantidade inválida ou acima do disponível.'); }

                        let updated = false;
                        if (currentUid) {
                            for (let i = 0; i < curHolders.length; i++) {
                                const h = curHolders[i];
                                if (h.uid && h.uid === currentUid) {
                                    curHolders[i] = {
                                        uid: h.uid,
                                        name: name || h.name || '',
                                        qty: (h.qty || 0) + qty,
                                        ts: Date.now()
                                    };
                                    updated = true;
                                    break;
                                }
                            }
                        }
                        if (!updated) {
                            curHolders.push({
                                uid: currentUid || null,
                                name: name || '',
                                qty: qty,
                                ts: Date.now()
                            });
                        }
                        const newTotal = curHolders.reduce((ss, h) => ss + (h.qty || 0), 0);
                        tx.set(docRef, {
                            max: curMax,
                            holders: curHolders,
                            reservedTotal: newTotal,
                            updatedAt: serverTimestamp()
                        });
                    });
                    showThankYouModal();
                } catch (err) {
                    console.error('[reserve-firebase] Erro ao reservar (detalhe):', err);
                    alert('Não foi possível reservar: ' + (err && err.message ? err.message : String(err)));
                }
            });
            buyArea.appendChild(reserveBtn);
        }
    }

    if (remaining === 0) {
        row.classList.add('reserved');
        row.setAttribute('aria-disabled', 'true');
    } else {
        row.classList.remove('reserved');
        row.removeAttribute('aria-disabled');
    }
    row.dataset.remaining = String(remaining);
}

function renderReservedUILocal(row, url) {
    const buyArea = row.querySelector('.buy-area');
    if (!buyArea) return;
    buyArea.innerHTML = '';
    const meta = localReserved[url] || {};
    const holders = Array.isArray(meta.holders) ? meta.holders : [];
    const reservedTotal = holders.reduce((s, h) => s + (h.qty || 0), 0);
    const max = meta.max || parseInt(row.dataset.max, 10) || 1;
    const remaining = Math.max(0, max - reservedTotal);

    const badge = document.createElement('span');
    badge.className = 'reserved-badge';

    if (holders.length === 0) {
        const text = document.createElement('span');
        text.textContent = 'Reservado';
        badge.appendChild(text);
    } else {
        const text = document.createElement('span');
        text.textContent = 'Reservado por: ';
        badge.appendChild(text);
        const list = document.createElement('span');
        list.className = 'reserved-list';
        const parts = holders.map(h => {
            const name = h.name && h.name.trim() ? h.name.trim() : 'Convidado';
            return `${name} (${h.qty || 1})`;
        });
        list.textContent = parts.join(', ');
        badge.appendChild(list);
    }

    buyArea.appendChild(badge);

    // simple undo for local: remove last holder created in this browser
    const undo = document.createElement('button');
    undo.className = 'unreserve-link';
    undo.type = 'button';
    undo.textContent = 'Cancelar minha reserva (local)';
    undo.addEventListener('click', () => {
        if (!localReserved[url] || !Array.isArray(localReserved[url].holders)) return;
        localReserved[url].holders.pop();
        if (localReserved[url].holders.length === 0) {
            delete localReserved[url];
        }
        saveLocalReserved();
        initRow(row);
    });

    buyArea.appendChild(undo);

    if (remaining === 0) {
        row.classList.add('reserved');
        row.setAttribute('aria-disabled', 'true');
    } else {
        row.classList.remove('reserved');
        row.removeAttribute('aria-disabled');
    }
    row.dataset.remaining = String(remaining);
}

// ---------- Thank you modal ----------
function showThankYouModal() {
    if (document.getElementById('reserve-thanks-modal')) return;

    const overlay = document.createElement('div');
    overlay.id = 'reserve-thanks-modal';
    overlay.className = 'modal-overlay';
    overlay.innerHTML = `
    <div class="modal-dialog" role="dialog" aria-modal="true" aria-labelledby="thanks-title">
      <h3 id="thanks-title" style="margin-top:0;">Obrigada!</h3>
      <p>Nós, da Família Fagundes Sol, agradecemos de todo o coração pelo presente! Que venha com saúde e muito amor, Apollo!!</p>
      <div style="text-align:center; margin-top:12px;">
        <button id="thanks-ok" class="choice-button" type="button">Fechar</button>
      </div>
    </div>
  `;
    document.body.appendChild(overlay);

    const ok = document.getElementById('thanks-ok');
    if (ok) ok.focus();
    overlay.addEventListener('click', (e) => { if (e.target === overlay) overlay.remove(); });
    ok && ok.addEventListener('click', () => overlay.remove());
}

// ---------- Build buy area (handles Firebase path too) ----------
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
        const declaredMax = row.dataset.max ? parseInt(row.dataset.max, 10) : 1;
        console.log('[reserve-firebase] Reservar clicado — url=', url, ' currentUid=', currentUid, ' USE_FIREBASE=', USE_FIREBASE, ' declaredMax=', declaredMax);

        const name = prompt('Tem certeza? (Opcional) Digite seu nome para aparecer na reserva.\nDeixe vazio para "Reservado com carinho".', '') || '';
        if (name === null) return;

        if (USE_FIREBASE) {
            const docRef = doc(db, 'reservas', docIdFromUrl(url));
            try {
                const snap = await getDoc(docRef);
                const cur = snap.exists() ? (snap.data() || {}) : {};
                const max = (typeof cur.max === 'number') ? cur.max : declaredMax || 1;
                const holders = Array.isArray(cur.holders) ? cur.holders : [];
                const reservedTotal = holders.reduce((s, h) => s + (h.qty || 0), 0);
                const remaining = Math.max(0, max - reservedTotal);
                if (remaining <= 0) { alert('Desculpe — não há mais unidades disponíveis desse item.'); return; }

                let qtyStr = prompt(`Quantos desse item você quer reservar? Disponíveis: ${remaining}`, '1');
                if (qtyStr === null) return;
                const qty = Math.max(0, parseInt(qtyStr, 10) || 0);
                if (!qty || qty < 1 || qty > remaining) { alert('Quantidade inválida ou acima do disponível.'); return; }

                await runTransaction(db, async (tx) => {
                    const s = await tx.get(docRef);
                    const base = s.exists() ? (s.data() || {}) : {};
                    const curMax = (typeof base.max === 'number') ? base.max : max;
                    const curHolders = Array.isArray(base.holders) ? base.holders.slice() : [];
                    const curTotal = curHolders.reduce((ss, h) => ss + (h.qty || 0), 0);
                    if (curTotal + qty > curMax) throw new Error('Quantidade insuficiente disponível (conflito de reserva).');

                    let updated = false;
                    if (currentUid) {
                        for (let i = 0; i < curHolders.length; i++) {
                            const h = curHolders[i];
                            if (h.uid && h.uid === currentUid) {
                                // use client timestamp for holder entry to avoid serverTimestamp inside array
                                curHolders[i] = {
                                    uid: h.uid,
                                    name: name || h.name || '',
                                    qty: (h.qty || 0) + qty,
                                    ts: Date.now()
                                };
                                updated = true;
                                break;
                            }
                        }
                    }
                    if (!updated) {
                        curHolders.push({
                            uid: currentUid || null,
                            name: name || '',
                            qty: qty,
                            ts: Date.now() // client timestamp for array element
                        });
                    }
                    const newTotal = curHolders.reduce((ss, h) => ss + (h.qty || 0), 0);
                    tx.set(docRef, {
                        max: curMax,
                        holders: curHolders,
                        reservedTotal: newTotal,
                        updatedAt: serverTimestamp()
                    });
                });

                console.log('[reserve-firebase] Reserva escrita com sucesso para url=', url, ' qty=', qty);
                showThankYouModal();
            } catch (err) {
                console.error('[reserve-firebase] Erro ao reservar (detalhe):', err);
                alert('Não foi possível reservar: ' + (err && err.message ? err.message : String(err)));
            }
        } else {
            if (!url) return;
            loadLocalReserved();
            const meta = localReserved[url] || { max: declaredMax || 1, holders: [] };
            const reservedTotal = (meta.holders || []).reduce((s, h) => s + (h.qty || 0), 0);
            const remaining = Math.max(0, (meta.max || declaredMax || 1) - reservedTotal);
            if (remaining <= 0) { alert('Desculpe — não há mais unidades disponíveis desse item (local).'); return; }

            let qtyStr = prompt(`Quantos desse item você quer reservar? Disponíveis: ${remaining}`, '1');
            if (qtyStr === null) return;
            const qty = Math.max(0, parseInt(qtyStr, 10) || 0);
            if (!qty || qty < 1 || qty > remaining) { alert('Quantidade inválida ou acima do disponível.'); return; }

            meta.holders = meta.holders || [];
            meta.holders.push({ name: name || '', qty: qty, ts: Date.now() });
            meta.max = meta.max || declaredMax || 1;
            localReserved[url] = meta;
            saveLocalReserved();
            renderReservedUILocal(row, url);
            showThankYouModal();
        }
    });
}

// ---------- helper to initialize a single row ----------
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

    buildBuyAreaLocal(row);
}

// ---------- init listeners ----------
async function initListeners() {
    if (!USE_FIREBASE) {
        loadLocalReserved();
        document.querySelectorAll('.item-row').forEach(initRow);

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

    await ensureAnonymousAuth();

    const rows = Array.from(document.querySelectorAll('.item-row'));
    for (const row of rows) {
        const url = row.dataset.url;
        if (!url) {
            buildBuyAreaLocal(row);
            continue;
        }
        const docRef = doc(db, 'reservas', docIdFromUrl(url));
        onSnapshot(docRef, (snap) => {
            if (snap.exists()) {
                const data = snap.data();
                renderReservedUIRemote(row, data);
            } else {
                row.classList.remove('reserved');
                row.removeAttribute('aria-disabled');
                buildBuyAreaLocal(row);
            }
        }, (err) => {
            console.error('[reserve-firebase] snapshot err', err);
            buildBuyAreaLocal(row);
        });
    }

    // dynamic additions
    const main = document.querySelector('main') || document.body;
    const observer = new MutationObserver((mutations) => {
        for (const m of mutations) {
            for (const node of m.addedNodes) {
                if (!(node instanceof HTMLElement)) continue;
                node.querySelectorAll && node.querySelectorAll('.item-row').forEach((r) => {
                    const url = r.dataset.url;
                    if (!url) { initRow(r); return; }
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
    initListeners().catch((err) => console.error('[reserve-firebase] Fallback init failed', err));
} else {
    initListeners().catch((err) => {
        console.error('[reserve-firebase] Init Firebase reserve failed', err);
        document.querySelectorAll('.item-row').forEach(initRow);
    });
}