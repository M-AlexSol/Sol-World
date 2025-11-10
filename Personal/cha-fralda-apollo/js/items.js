// ...new file...
/* items.js
   Torna a lista de presentes expansível: clique (ou Enter/Space) abre detalhes com botão Comprar.
*/
(function(){
  'use strict';

  function toggleRow(li, expand){
    expand = (typeof expand === 'boolean') ? expand : (li.getAttribute('aria-expanded') !== 'true');
    li.setAttribute('aria-expanded', expand ? 'true' : 'false');
    var detail = li.querySelector('.row-detail');
    if(detail) detail.setAttribute('aria-hidden', expand ? 'false' : 'true');
    if(expand){
      // fechar outros (opcional): manter só um aberto
      document.querySelectorAll('.item-row[aria-expanded="true"]').forEach(function(openLi){
        if(openLi !== li){ openLi.setAttribute('aria-expanded','false'); var d=openLi.querySelector('.row-detail'); if(d) d.setAttribute('aria-hidden','true'); }
      });
      // scroll para visibilidade suave
      li.scrollIntoView({behavior:'smooth', block:'center'});
    }
  }

  function onActivate(e){
    var li = e.currentTarget;
    // ignore clicks on the buy link itself
    if(e.type === 'click'){
      // handled below: toggle
    }
    toggleRow(li);
  }

  function onKey(e){
    if(e.key === 'Enter' || e.key === ' '){
      e.preventDefault();
      toggleRow(e.currentTarget);
    } else if(e.key === 'Escape'){
      // collapse if open
      var li = e.currentTarget;
      if(li.getAttribute('aria-expanded') === 'true') toggleRow(li, false);
    }
  }

  function init(){
    var rows = document.querySelectorAll('.item-row');
    if(!rows || !rows.length) return;
    rows.forEach(function(li){
      var main = li.querySelector('.row-main');
      if(main){
        // make main clickable via its parent li; attach handlers on li for keyboard/focus
        li.addEventListener('click', function(e){
          // avoid toggling when click on links/buttons inside row-detail
          if(e.target.closest('a') || e.target.closest('button')) return;
          toggleRow(li);
        });
        li.addEventListener('keydown', function(e){
          if(e.key === 'Enter' || e.key === ' ') { e.preventDefault(); toggleRow(li); }
          else if(e.key === 'Escape' && li.getAttribute('aria-expanded') === 'true'){ toggleRow(li,false); }
        });
        // set initial ARIA attributes
        li.setAttribute('aria-expanded','false');
        var detail = li.querySelector('.row-detail');
        if(detail) detail.setAttribute('aria-hidden','true');
      }
    });
  }

  if(document.readyState === 'loading'){
    document.addEventListener('DOMContentLoaded', init);
  } else init();
})();