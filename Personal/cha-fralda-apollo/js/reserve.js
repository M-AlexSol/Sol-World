// Reserva por item via botão "Reservar" ao lado do link de compra.
// Persiste localmente com localStorage (chave: 'apollo:reserved').
// - Corrige o problema de "trava" ao cancelar (reconstrói a área de compra).
// - Adiciona campo opcional "nome" na confirmação e exibe "Reservado por: NOME" (ou "Reservado com carinho").

(function () {
  const STORAGE_KEY = 'apollo:reserved';
  let reserved = {};

  function load() {
    try {
      reserved = JSON.parse(localStorage.getItem(STORAGE_KEY) || '{}');
    } catch (e) {
      reserved = {};
    }
  }
  function save() {
    try {
      localStorage.setItem(STORAGE_KEY, JSON.stringify(reserved));
    } catch (e) { /* ignore */ }
  }

  // Modal confirm com campo opcional 'nome' - resolve com {ok: boolean, name: string}
  function confirmModal(message) {
    return new Promise((resolve) => {
      const overlay = document.createElement('div');
      overlay.className = 'modal-overlay';
      overlay.innerHTML = `
        <div class="modal-dialog" role="dialog" aria-modal="true" aria-labelledby="reserve-title">
          <h3 id="reserve-title">Confirmação de reserva</h3>
          <p>${message}</p>
          <label style="font-size:0.95rem;color:#333;display:block;margin-bottom:8px;">
            <span style="font-weight:700;margin-right:8px;">Opcional:</span> Digite seu nome (aparecerá na reserva)
          </label>
          <input type="text" placeholder="Seu nome (opcional)" aria-label="Seu nome">
          <div class="modal-actions">
            <button class="btn cancel" type="button">Cancelar</button>
            <button class="btn confirm" type="button">Tenho certeza — Reservar</button>
          </div>
        </div>
      `;
      document.body.appendChild(overlay);

      const cancelBtn = overlay.querySelector('.btn.cancel');
      const confirmBtn = overlay.querySelector('.btn.confirm');
      const input = overlay.querySelector('input[type="text"]');

      function cleanup(result) {
        overlay.remove();
        resolve(result);
      }

      cancelBtn.addEventListener('click', () => cleanup({ ok: false }));
      confirmBtn.addEventListener('click', () => {
        const name = (input.value || '').trim();
        cleanup({ ok: true, name: name });
      });

      overlay.addEventListener('click', (e) => {
        if (e.target === overlay) cleanup({ ok: false });
      });
      document.addEventListener('keydown', function onKey(e) {
        if (e.key === 'Escape') {
          document.removeEventListener('keydown', onKey);
          cleanup({ ok: false });
        }
      });

      // focus input for convenience
      input.focus();
    });
  }

  // cria buy + reserve UI dentro do buy-area (reconstrói a área)
  function buildBuyArea(row) {
    const url = row.dataset.url;
    const buyArea = row.querySelector('.buy-area');
    if (!buyArea) return;

    // Clear and build: buy button (anchor) + reserve button
    buyArea.innerHTML = '';

    // create buy anchor
    const buyAnchor = document.createElement('a');
    buyAnchor.className = 'choice-button buy-button';
    buyAnchor.href = url || '#';
    buyAnchor.target = '_blank';
    buyAnchor.rel = 'noopener noreferrer';
    buyAnchor.textContent = 'Abrir na Loja';

    // create reserve button
    const reserveBtn = document.createElement('button');
    reserveBtn.className = 'reserve-button';
    reserveBtn.type = 'button';
    reserveBtn.textContent = 'Reservar';

    buyArea.appendChild(buyAnchor);
    buyArea.appendChild(reserveBtn);

    // attach behavior on reserve button
    reserveBtn.addEventListener('click', async (ev) => {
      ev.preventDefault();
      const msg = 'Tem certeza? O item ficará indisponível para quem visualizar a página neste navegador.';
      const resp = await confirmModal(msg);
      if (!resp || !resp.ok) return;
      // save reservation with optional name
      const name = resp.name && resp.name.length ? resp.name : '';
      if (!url) return;
      reserved[url] = { ts: Date.now(), by: 'local', name: name };
      save();
      renderReservedUI(row, url);
    });
  }

  // renderiza UI para item reservado (badge + undo)
  function renderReservedUI(row, url) {
    const buyArea = row.querySelector('.buy-area');
    if (!buyArea) return;
    buyArea.innerHTML = '';

    const meta = reserved[url] || {};
    const name = meta.name || '';
    const badge = document.createElement('span');
    badge.className = 'reserved-badge';
    // texto do badge com nome (se houver)
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
      // remove reservation and restore buy area
      delete reserved[url];
      save();
      // rebuild buy area
      initRow(row);
    });

    buyArea.appendChild(badge);
    buyArea.appendChild(undo);

    row.classList.add('reserved');
    row.setAttribute('aria-disabled', 'true');
  }

  // initialize single row: rebuild buy area or mark reserved
  function initRow(row) {
    const url = row.dataset.url;
    // remove any previous reserved class
    row.classList.remove('reserved');
    row.removeAttribute('aria-disabled');

    if (url && reserved[url]) {
      renderReservedUI(row, url);
      return;
    }

    // otherwise build buy area (buy + reserve)
    buildBuyArea(row);
  }

  function initAll() {
    load();
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
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initAll);
  } else initAll();
})();