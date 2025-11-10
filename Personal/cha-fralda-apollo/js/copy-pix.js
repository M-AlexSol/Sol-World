/* ALTERAÇÃO: copia a chave PIX e mostra toast fixo por 5s (acessível, não desloca layout) */
(function(){
  'use strict';

  var PIX_KEY = '857ed555-b4b6-4606-a688-931e35a388df';
  var btn = document.getElementById('copy-pix');

  function createToast(text, ok){
    // remove antigo se existir
    var existing = document.getElementById('pix-toast');
    if(existing){
      clearTimeout(existing._t);
      existing.parentNode.removeChild(existing);
    }

    var toast = document.createElement('div');
    toast.id = 'pix-toast';
    toast.setAttribute('role','status');
    toast.setAttribute('aria-live','polite');
    toast.style.position = 'fixed';
    toast.style.left = '50%';
    toast.style.bottom = '24px';
    toast.style.transform = 'translateX(-50%)';
    toast.style.background = ok ? '#2a7d32' : '#c33';
    toast.style.color = '#fff';
    toast.style.padding = '12px 16px';
    toast.style.borderRadius = '10px';
    toast.style.boxShadow = '0 8px 30px rgba(0,0,0,0.18)';
    toast.style.fontWeight = '700';
    toast.style.zIndex = '200000';
    toast.style.opacity = '0';
    toast.style.transition = 'opacity .18s ease, transform .18s ease';
    toast.textContent = text || (ok ? 'Copiado para a Área de Transferência' : 'Erro ao copiar');

    document.body.appendChild(toast);
    // for small entrance animation
    requestAnimationFrame(function(){
      toast.style.opacity = '1';
      toast.style.transform = 'translateX(-50%) translateY(0)';
    });

    // hide after 5s
    toast._t = setTimeout(function(){
      toast.style.opacity = '0';
      toast.style.transform = 'translateX(-50%) translateY(8px)';
      setTimeout(function(){ if(toast.parentNode) toast.parentNode.removeChild(toast); }, 200);
    }, 5000);

    return toast;
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
    if(navigator.clipboard && navigator.clipboard.writeText){
      navigator.clipboard.writeText(PIX_KEY).then(function(){
        createToast('Chave PIX copiada para a Área de Transferência', true);
        btn.focus();
      }).catch(function(){
        var ok = fallbackCopy(PIX_KEY);
        createToast(ok ? 'Chave PIX copiada para a Área de Transferência' : 'Erro ao copiar', ok);
      });
    } else {
      var ok = fallbackCopy(PIX_KEY);
      createToast(ok ? 'Chave PIX copiada para a Área de Transferência' : 'Erro ao copiar', ok);
    }
  });
})();