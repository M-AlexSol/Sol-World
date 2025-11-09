// ...existing code...
/* ALTERAÇÃO: verificação case-sensitive — gera letras maiúsculas e minúsculas e compara exatamente */
(function(){
  'use strict';

  try { console.log('auth.js loaded —', location.href); } catch(e){}

  var overlayId = 'auth-overlay';
  var canvasId = 'captcha-canvas';
  var inputId = 'captcha-input';
  var refreshId = 'captcha-refresh';
  var verifyId = 'captcha-verify';
  var cancelId = 'captcha-cancel';
  var msgId = 'captcha-msg';
  var storageKey = 'human_verified_v1';

  function elt(id){ try { return document.getElementById(id); } catch(e){ return null; } }

  // ALTERAÇÃO: inclui letras minúsculas para possibilitar verificação case-sensitive
  function randCode(len){
    var chars = '23456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghjkmnpqrstuvwxyz'; // evita 0/O,1/I, evita l/1 confusion
    var s = '';
    for(var i=0;i<len;i++) s += chars[Math.floor(Math.random()*chars.length)];
    return s;
  }

  function drawCaptcha(code){
    var c = elt(canvasId);
    if(!c || !c.getContext) return;
    var ctx = c.getContext('2d');
    var w = c.width, h = c.height;
    try {
      ctx.clearRect(0,0,w,h);
      ctx.fillStyle = '#f6f9ff';
      ctx.fillRect(0,0,w,h);

      for(var i=0;i<6;i++){
        ctx.strokeStyle = 'rgba(60,118,210,' + (0.06 + Math.random()*0.12) + ')';
        ctx.lineWidth = 1 + Math.random()*1.5;
        ctx.beginPath();
        ctx.moveTo(Math.random()*w, Math.random()*h);
        ctx.lineTo(Math.random()*w, Math.random()*h);
        ctx.stroke();
      }

      var x = 12;
      for(var i=0;i<code.length;i++){
        var ch = code[i];
        ctx.save();
        var fontSize = 22 + Math.floor(Math.random()*8);
        ctx.font = fontSize + 'px sans-serif';
        ctx.fillStyle = (Math.random()>0.5) ? '#12386a' : '#214a77';
        var angle = (Math.random()-0.5) * 0.5;
        ctx.translate(x, h/2 + (Math.random()*6-3));
        ctx.rotate(angle);
        ctx.fillText(ch, 0, 0);
        ctx.restore();
        x += fontSize - 6;
      }

      for(var j=0;j<30;j++){
        ctx.fillStyle = 'rgba(33,74,119,' + (0.06 + Math.random()*0.15) + ')';
        ctx.beginPath();
        ctx.arc(Math.random()*w, Math.random()*h, Math.random()*1.4 + 0.4, 0, Math.PI*2);
        ctx.fill();
      }
    } catch(e){
      try { console.warn('drawCaptcha error', e); } catch(err) {}
    }
  }

  function showMessage(text, isError){
    var el = elt(msgId);
    if(!el) return;
    try {
      el.textContent = text || '';
      el.style.color = isError ? '#c33' : '#2a7d32';
    } catch(e){}
  }

  function hideOverlay(){
    var ov = elt(overlayId);
    if(!ov) return;
    try {
      ov.style.transition = 'opacity .22s ease';
      ov.style.opacity = 0;
      setTimeout(function(){ ov.style.display = 'none'; ov.setAttribute('aria-hidden','true'); }, 230);
    } catch(e){}
  }

  function init(){
    var ov = elt(overlayId);
    if(!ov) return;

    try {
      if(window.sessionStorage && sessionStorage.getItem(storageKey) === 'true'){
        ov.style.display = 'none';
        ov.setAttribute('aria-hidden','true');
        try { console.log('auth.js: sessionStorage indicates verified'); } catch(e){}
        return;
      }
    } catch(e){}

    var code = randCode(5);
    drawCaptcha(code);

    function regenerate(){
      code = randCode(5);
      drawCaptcha(code);
      showMessage('', false);
      var inp = elt(inputId); if(inp) inp.value = '';
    }

    var btnRefresh = elt(refreshId);
    if(btnRefresh) try { btnRefresh.addEventListener('click', regenerate); } catch(e){}

    var btnVerify = elt(verifyId);
    if(btnVerify) btnVerify.addEventListener('click', function(){
      // ALTERAÇÃO: não força uppercase — verificação é sensível a caixa
      var v = (elt(inputId) && elt(inputId).value || '').replace(/[^A-Za-z0-9]/g,'').trim();
      if(!v){
        showMessage('Digite o código', true);
        return;
      }
      if(v === code){
        try { sessionStorage.setItem(storageKey,'true'); } catch(e){}
        showMessage('Verificado — carregando...', false);
        setTimeout(hideOverlay, 250);
        try { console.log('auth.js: verification success'); } catch(e){}
      } else {
        showMessage('Código incorreto — tente novamente', true);
        try { console.log('auth.js: verification failure'); } catch(e){}
        setTimeout(regenerate, 700);
      }
    });

    var btnCancel = elt(cancelId);
    if(btnCancel) try { btnCancel.addEventListener('click', function(){
      showMessage('Acesso bloqueado sem verificação', true);
    }); } catch(e){}

    var inp = elt(inputId);
    if(inp){
      inp.addEventListener('keydown', function(e){
        if(e.key === 'Enter') { e.preventDefault(); if(btnVerify) btnVerify.click(); }
      });
      try { inp.focus(); } catch(e){}
    }
  }

  if(document.readyState === 'loading'){
    document.addEventListener('DOMContentLoaded', init);
  } else init();

})();