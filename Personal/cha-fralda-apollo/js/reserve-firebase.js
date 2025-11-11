// Reserva compartilhada via Firebase Firestore + Auth (anônimo).
// Substitua o objeto FIREBASE_CONFIG abaixo com o config do seu app Firebase.

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

const FIREBASE_CONFIG = {
    apiKey: "AIzaSyA2DAL7nb37MV0sxT4benzpHC_kkYj6G18",
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

// sign in anon
async function ensureAnonymousAuth() {
    return new Promise((resolve, reject) => {
        onAuthStateChanged(auth, (user) => {
            if (user) {
                currentUid = user.uid;
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
            console.error('Erro ao reservar:', err);
            alert('Não foi possível reservar (pode já estar reservado).');
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
    console.error('Init Firebase reserve failed', err);
    // fallback: rebuild local UI without real-time
    document.querySelectorAll('.item-row').forEach(buildBuyAreaLocal);
});