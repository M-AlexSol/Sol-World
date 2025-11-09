// ...existing code...
/* ALTERAÇÃO: contador de contagem regressiva para o período online
   (mesma lógica do script inline; usa defer no <script> do HTML) */
(function(){
  'use strict';

  // Período do evento (ajuste se necessário)
  var start = new Date('2025-11-09T00:00:00');
  var end   = new Date('2026-02-11T23:59:59');

  var el = document.getElementById('countdown-timer');
  var eventDateEl = document.getElementById('event-date');
  if(eventDateEl) eventDateEl.textContent = "09/11/2025 até 11/02/2026";

  function pad(n){ return n < 10 ? '0'+n : n; }

  function update(){
    var now = new Date();
    if(!el) return;

    if(now < start){
      el.textContent = 'Começa em ' + start.toLocaleDateString();
      return;
    }

    var diff = end.getTime() - now.getTime();
    if(diff <= 0){
      el.textContent = 'Período encerrado';
      clearInterval(timer);
      return;
    }

    var days = Math.floor(diff / (1000*60*60*24));
    var hrs  = Math.floor((diff % (1000*60*60*24)) / (1000*60*60));
    var mins = Math.floor((diff % (1000*60*60)) / (1000*60));
    var secs = Math.floor((diff % (1000*60)) / 1000);

    el.innerHTML = '<span style="display:block;font-size:16px;color:#666;margin-bottom:4px">Nascimento do Apollo (Previsão)</span>' +
                   '<span style="font-size:16px">' + pad(days) + 'd ' + pad(hrs) + 'h ' + pad(mins) + 'm ' + pad(secs) + 's</span>';
  }

  update();
  var timer = setInterval(update, 1000);
})();