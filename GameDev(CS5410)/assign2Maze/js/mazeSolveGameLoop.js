/* globals mazeSolve, $, requestAnimationFrame */
'use strict';

mazeSolveGameLoop = (function(that){
  var lastTime;
  var won = false;

  that.start = function () {
    that.time = 0;
    lastTime = Date.now();
    that.solve();
    requestAnimationFrame(gameLoop);
  };

  function gameLoop(time) {
    var deltaTime = time - lastTime;
    // The delta time on start sometimes is greater than 10 seconds and it messes
    // up the timing. So if it is really large or negative than I set it to 1 ms
    if(Math.abs(deltaTime) > 10 * 1000) deltaTime = 1;

    if(won) return doWin();

    update(deltaTime);
    render();

    lastTime = time;

    requestAnimationFrame(gameLoop);
  }

  function update(deltaTime) {
    that.time += deltaTime;

    while(that.eventQueue.length) {
      var theEvent = that.eventQueue.pop();

      if(
        theEvent === 'UP' || theEvent === 'DOWN' ||
        theEvent === 'LEFT' || theEvent === 'RIGHT'
      ) {
        that.controls.HINT = false;
        if(that.canMove(theEvent)) that.makeMove(theEvent);
      } else {
        that.toggleControl(theEvent);
      }

      if(win()) won = true;
    }
  }

  function render() {
    that.showTime(getTimeStamp(that.time));
    that.showScore();
    that.checkButtonStatus();
    that.draw('maze-canvas');
  }

  function doWin() {
    addScore(getDateStamp(), that.time, that.score, '' + that.width + 'x' + that.height);

    that.controls.SCORE = true;
    that.controls.OPTIMAL_PATH = true;
    that.controls.BREAD = true;

    render();

    var winDiv = $('.win-div');
    winDiv.removeAttr('hidden');
  }

  function getTimeStamp(time) {
    var seconds = Math.floor(time/1000 % 60);
    var minutes = Math.floor(time/(1000*60) % 60);
    var ms = Math.floor(time%1000 / 10);

    return pad2Digits(minutes) + ':' + pad2Digits(seconds) + '.' + pad2Digits(ms);
  }

  function getDateStamp() {
    var date = new Date();
    return date.getFullYear() + '-' + pad2Digits(date.getMonth()+1) + '-' + pad2Digits(date.getDate());
  }

  function pad2Digits(value) {
    return (+value < 10) ? '0' + value : value;
  }

  function addScore(date, time, score, size) {
    var highScores = localStorage.highScores || {};

    if(typeof highScores == 'string') highScores = JSON.parse(highScores);

    highScores[size+','+time+','+score+','+date] = {
      date: date,
      timeStamp: getTimeStamp(time),
      time: time,
      score: score,
      size: size
    };

    localStorage.highScores = JSON.stringify(highScores);
  }

  function win() {
    return that.player.x === that.width-1 && that.player.y === that.height-1;
  }

}(mazeSolve));