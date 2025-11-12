# Chá de Fralda do Apollo
Este documento descreve, em detalhes, a arquitetura, componentes, decisões técnicas e recomendações de segurança do projeto "Chá de Fralda do Apollo". Contém orientações para rodar localmente, testar integrações (Firebase), e passos operacionais importantes (como rotação de chaves e publicação de regras).

## Sumário
- Visão geral
- Linguagens e bibliotecas
- Estrutura de arquivos (mapa e propósito)
- Fluxo de reserva (cliente e backend)
- Modelo de dados (Firestore)
- Regras de segurança Firestore recomendadas
- Autenticação e App Check
- Armazenamento local (fallback)
- Segurança: tratamento de chaves e configuração em runtime
- Como rodar e testar localmente
- Debug e ferramentas (Rules Playground)
- Limitações, riscos e recomendações futuras
- Checklist de entrega / manutenção

---

## Visão geral
Site estático (HTML/CSS/vanilla JS) que apresenta uma lista de presentes para o Chá de Fralda e permite que visitantes:
- visualizem a lista,
- vejam contagem regressiva do evento,
- façam PIX (QR + copiar chave),
- reservem itens — localmente (fallback) ou globalmente (compartilhado) via Firebase Firestore com Auth anônima.

A integração com Firestore foi implementada para que reservas sejam visíveis para todos visitantes (modo compartilhado). Há um fallback local utilizando `localStorage` quando a configuração do Firebase não está presente.

---

## Linguagens e bibliotecas
- HTML5 — `index.html`
- CSS3 — `css/styles.css`
- JavaScript (ES modules) — `js/*.js`
  - Firebase JS SDK v9 (modular): `firebase-app`, `firebase-auth`, `firebase-firestore`
- Ferramentas de desenvolvimento: servidor estático local (por exemplo, `python3 -m http.server` ou extensão Live Server)

Bibliotecas externas (CDN):
- Firebase SDK (9.22.1)
- QR code no `index.html` utiliza `api.qrserver.com` (para gerar a imagem QR)

---

## Estrutura de arquivos (principais)
Caminho do projeto: `Personal/cha-fralda-apollo/`

- `index.html` — página principal (interface). Alterações recentes:
  - Data do evento: `09/11/2025 até 30/12/2025`
  - Botões de loja renomeados para "Sugestão de Loja"
  - Texto com link WhatsApp adicionado abaixo do título da lista
  - Inclui `<script src="config.js"></script>` antes do módulo Firebase
- `css/styles.css` — estilos globais (inclui classes para UI da reserva, modal, badge etc.)
- `js/countdown.js` — contador regressivo para o evento
- `js/views.js` — lógica de troca de views (home / PIX / lista)
- `js/copy-pix.js` — copia chave PIX para clipboard
- `js/items.js` — interações de itens (expansão de linhas etc.)
- `js/reserve-firebase.js` — módulo principal de reserva (suporta modo compartilhado via Firebase e fallback local)
  - Funcionalidades:
    - Inicialização guardada do Firebase somente quando `window.__FIREBASE_CONFIG__` existe
    - Autenticação anônima (quando em modo Firebase)
    - `onSnapshot` listeners (updates em tempo real)
    - Transações (`runTransaction`) para evitar overbooking
    - Local fallback: usa `localStorage` (chave `apollo:reserved_local_v1`)
    - Multi-quantidade por item (`data-max` em `li.item-row`)
    - Modal de agradecimento
- `config.js` (Não comitado) — arquivo local a ser criado pelo deploy/host, define:
  - `window.__FIREBASE_CONFIG__ = { apiKey: "...", projectId: "...", ... }`
  - Deve estar listado em `.gitignore`
- `README.md` — documentação (este arquivo será substituído pelo laudo técnico)
- `images/*` — imagens estáticas (header, ícones)

---

## Fluxo de reserva (resumo)
1. Usuário abre `index.html` e a página carrega `config.js` (se presente).
2. `js/reserve-firebase.js` detecta presença de `window.__FIREBASE_CONFIG__`:
   - Se presente: inicializa Firebase, faz `signInAnonymously` (se necessário) e cria `onSnapshot` em cada `reservas/{docId}`.
   - Se ausente: ativa fallback local (localStorage).
3. UI por item (`li.item-row`) exibe:
   - badge de quem reservou (`Reservado por: Nome (qty)`)
   - botão "Cancelar minha reserva" para quem já tem reserva
   - se restante > 0 e visitante NÃO reservou ainda: mostra botão `Reservar` (com quantidade disponível).
4. No modo compartilhado (Firestore), ao reservar:
   - Cliente abre prompt para nome e quantidade.
   - Executa `runTransaction` para ler documento, verificar disponibilidade e atualizar `holders` array + `reservedTotal`.
   - `holders` usa timestamps de cliente (`Date.now()`), `updatedAt` usa `serverTimestamp()` (top-level).
   - `onSnapshot` atualiza UIs de todos visitantes em tempo real.

---

## Modelo de dados (Firestore)
Coleção: `reservas`

Documento por item:
- docId: `encodeURIComponent(itemUrl)` — por exemplo: `https%3A%2F%2Fwww.tiptop.com.br%2F...`
- Exemplo de documento:
```json
{
  "max": 3,
  "holders": [
    { "uid": "PPcMuL...", "name": "João", "qty": 1, "ts": 1762917552387 },
    { "uid": null, "name": "Maria", "qty": 1, "ts": 1762917600000 }
  ],
  "reservedTotal": 2,
  "updatedAt": "<serverTimestamp>"
}