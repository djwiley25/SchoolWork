/* globals $ */
'use strict';

var mazeSolve = (function() {
    function bindButtonTouchClick() {
        $('button').on('touchend click', function (e) {
        e.stopPropagation();
  
        var button = $(e.target);
  
        var size = button.html().split('x');
        var width = size[0] || 5;
        var height = size[1] || 5;
  
        window.location = 'maze.html' + '#/' + width + '/' + height;
      });
    }

  $(document).ready(function() {
    $('#scores').click(goTo('scores.html'));
  });

  $(document).ready(bindButtonTouchClick);

  function goTo(page) {
    return function() {
      window.location = page;
    };
  }

}());