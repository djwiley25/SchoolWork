/* globals $, MazeSolver */
'use strict';

MazeSolver.mazeHTML = (function() {

  var dimensions = window.location.hash.split('/');
  var mazeWidth = +dimensions[1] || 5;
  var mazeHeight = +dimensions[2] || 7;

  MazeSolver.generate(mazeWidth, mazeHeight);

  var canvas = $('#maze-canvas');

  MazeSolver.draw(canvas[0]);

  MazeSolver.start();

  var lastTouch = false;

  function swipeDetector(x, y) {
    var maxTime = 500;

    var that = {
      x: x,
      y: y,
      time: Date.now()
    };

    that.getSwipe = function(x, y) {
      var swipe = {
        x: Math.abs(that.x - x),
        y: Math.abs(that.y - y),
        time: Date.now()
      };

      if(swipe.time - that.time > maxTime) return false;

      if(swipe.x > swipe.y) {
        return (x > that.x) ? 'RIGHT' : 'LEFT';
      }
      else {
        return (y > that.y) ? 'DOWN' : 'UP';
      }
    };

    return that;
  }

  window.addEventListener('touchstart', function (e) {
    var touch = e.changedTouches[0];
    lastTouch = swipeDetector(+touch.pageX, +touch.pageY);
  }, false);

  window.addEventListener('touchmove', function (e) {
    e.preventDefault();
    if(lastTouch) {
      var touch = e.changedTouches[0];
      var result = lastTouch.getSwipe(+touch.pageX, +touch.pageY);
      if(result) MazeSolver.addEvent(result);
      lastTouch = false;
    }
  }, false);

  /////////////// desktop key events //////////////////////

  window.addEventListener('keydown', function (e) {
    e.cancelBubble = true;
    var keyNum = e.which;
    var keyChar = String.fromCharCode(e.which);

    if     (keyNum === 37) MazeSolver.addEvent('LEFT');
    else if(keyNum === 38) MazeSolver.addEvent('UP');
    else if(keyNum === 39) MazeSolver.addEvent('RIGHT');
    else if(keyNum === 40) MazeSolver.addEvent('DOWN');

    else if(keyChar === 'A') MazeSolver.addEvent('LEFT');
    else if(keyChar === 'W') MazeSolver.addEvent('UP');
    else if(keyChar === 'D') MazeSolver.addEvent('RIGHT');
    else if(keyChar === 'S') MazeSolver.addEvent('DOWN');

    else if(keyChar === 'J') MazeSolver.addEvent('LEFT');
    else if(keyChar === 'I') MazeSolver.addEvent('UP');
    else if(keyChar === 'L') MazeSolver.addEvent('RIGHT');
    else if(keyChar === 'K') MazeSolver.addEvent('DOWN');

    else if(keyChar === 'H') MazeSolver.addEvent('HINT');
    else if(keyChar === 'B') MazeSolver.addEvent('BREAD');
    else if(keyChar === 'P') MazeSolver.addEvent('PATH');
    else if(keyChar === 'Y') MazeSolver.addEvent('SCORE');

    return true;
  });

  /////////////// buttons //////////////////////

  $('#HINT').click(addEvent('HINT'));
  $('#BREAD').click(addEvent('BREAD'));
  $('#PATH').click(addEvent('PATH'));
  $('#SCORE').click(addEvent('SCORE'));

  function addEvent(event) {
    return function() {
      MazeSolver.addEvent(event);
    };
  }

  $('#done').click(function() {
    window.location = 'index.html';
  });

  $('#again').click(function() {
    window.location.reload();
  });

}());