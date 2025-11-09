/* ALTERAÇÃO: copia a chave PIX para a área de transferência com fallback e mostra mensagem breve */
(function(){
  'use strict';

  var PIX_KEY = '857ed555-b4b6-4606-a688-931e35a388df'; // ALTERAÇÃO: chave a ser copiada
  var btn = document.getElementById('copy-pix');
  var msg = document.getElementById('copy-pix-msg');

  function showMsg(text, ok){
    if(!msg) return;
    msg.textContent = text || '';
    msg.style.color = ok ? '#2a7d32' : '#c33';
    msg.style.opacity = '1';
    clearTimeout(msg._t);
    msg._t = setTimeout(function(){ msg.style.opacity = '0'; }, 2000);
  }

  function fallbackCopy(text){
    var ta = document.createElement('textarea');
    ta.value = text;
    ta.setAttribute('readonly','');
    ta.style.position = 'absolute';
    ta.style.left = '-9999px';
    document.body.appendChild(ta);
    ta.select();
    try {
      var ok = document.execCommand('copy');
      document.body.removeChild(ta);
      return !!ok;
    } catch(e){
      document.body.removeChild(ta);
      return false;
    }
  }

  if(!btn) return;

  btn.addEventListener('click', function(){
    // Prefer navigator.clipboard when disponível (mais confiável)
    if(navigator.clipboard && navigator.clipboard.writeText){
      navigator.clipboard.writeText(PIX_KEY).then(function(){
        showMsg('Chave PIX copiada!', true);
        btn.focus();
      }).catch(function(){
        var ok = fallbackCopy(PIX_KEY);
        showMsg(ok ? 'Chave PIX copiada!' : 'Erro ao copiar', ok);
      });
    } else {
      var ok = fallbackCopy(PIX_KEY);
      showMsg(ok ? 'Chave PIX copiada!' : 'Erro ao copiar', ok);
    }
  });

})();