// ...existing code...
/* ALTERAÇÃO: toggle - se clicar novamente no botão ativo volta pro 'home' */
(function(){
  'use strict';

  var btnPix = document.getElementById('btn-pix');
  var btnList = document.getElementById('btn-list');
  var home = document.getElementById('home-view');
  var pix = document.getElementById('pix-view');
  var list = document.getElementById('list-view');

  function setActiveButton(activeBtn){
    [btnPix, btnList].forEach(function(b){
      if(!b) return;
      if(b === activeBtn){
        b.classList.add('active');
        b.setAttribute('aria-pressed','true');
      } else {
        b.classList.remove('active');
        b.setAttribute('aria-pressed','false');
      }
    });
  }

  function showView(which){
    if(which === 'pix'){
      if(pix) { pix.classList.remove('hidden'); pix.setAttribute('aria-hidden','false'); }
      if(list) { list.classList.add('hidden'); list.setAttribute('aria-hidden','true'); }
      if(home) { home.classList.add('hidden'); home.setAttribute('aria-hidden','true'); }
      setActiveButton(btnPix);
    } else if(which === 'list'){
      if(list) { list.classList.remove('hidden'); list.setAttribute('aria-hidden','false'); }
      if(pix) { pix.classList.add('hidden'); pix.setAttribute('aria-hidden','true'); }
      if(home) { home.classList.add('hidden'); home.setAttribute('aria-hidden','true'); }
      setActiveButton(btnList);
    } else {
      if(home) { home.classList.remove('hidden'); home.setAttribute('aria-hidden','false'); }
      if(pix) { pix.classList.add('hidden'); pix.setAttribute('aria-hidden','true'); }
      if(list) { list.classList.add('hidden'); list.setAttribute('aria-hidden','true'); }
      setActiveButton(null);
    }
    window.scrollTo({ top: 0, behavior: 'smooth' });
  }

  // NOVA FUNÇÃO: alterna (toggle) a view — se o botão já estiver ativo volta ao home
  function toggleView(which, btn){
    if(btn && btn.classList && btn.classList.contains('active')){
      showView('home');
    } else {
      showView(which);
    }
  }

  if(btnPix) btnPix.addEventListener('click', function(){ toggleView('pix', btnPix); });
  if(btnList) btnList.addEventListener('click', function(){ toggleView('list', btnList); });

  [btnPix, btnList].forEach(function(btn){
    if(!btn) return;
    btn.addEventListener('keydown', function(e){
      if(e.key === 'Enter' || e.key === ' ') { e.preventDefault(); btn.click(); }
    });
  });

  // Inicializa estado
  if(home) showView('home'); else showView(null);
})();