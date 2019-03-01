/* globals $ */

var MazeSolver = (function(){
    'use strict';
  
    var SCORES_TO_SHOW = 6;
  
    var scores = {};
  
    function getScores() {
      var highScores = localStorage.highScores || {};
  
      if(typeof highScores == 'string') highScores = JSON.parse(highScores);
  
      scores = {};
  
      for(var i in highScores) {
        var score = highScores[i];
  
        if(!scores[score.size]) scores[score.size] = [];
  
        scores[score.size].push(score);
      }
  
      for(var index in scores) {
        scores[index].splice(SCORES_TO_SHOW);
  
        scores[index].sort(scoreSort);
      }
    }
  
    function scoreSort(left, right) {
      if(left.time == right.time) {
        if(left.score == right.score) return 0;
        if(left.score >= right.score) return 1;
        if(left.score <= right.score) return -1;
      }
      if(left.time >= right.time) return -1;
      if(left.time <= right.time) return 1;
    }
  
    function displayScores() {
      var div = $('.scores');
      var sizes = [], size;
  
      for(size in scores) {
        sizes.push(size);
      }
  
      sizes.sort(function(left, right) {
        return +left.split('x')[0] < +right.split('x')[0];
      });
  
      for(var index in sizes) {
        size = sizes[index];
  
        var header = $('<h3>');
  
        header.attr('class', 'score-header');
        header.text(size);
  
        for(var i in scores[size]) {
          var score = scores[size][i];
  
          var p = $('<p>');
  
          p.attr('class', 'score');
          p.text('Time: ' + score.timeStamp + ' - ' + score.score + ' points  - ' + score.date);
  
          div.prepend(p);
        }
  
        div.prepend(header);
      }
    }
  
    $(document).ready(function() {
      getScores();
      displayScores();
  
      $('#clear').click(function() {
        localStorage.clear();
        $('.scores').html('');
        getScores();
        displayScores();
      });
    });
  
  }());
  
  // Example scores
  // "{"25x25,00:20.9,312,2014-02-11":{"date":"2014-02-11","time":"00:20.9","score":312,"size":"25x25"},"20x20,00:11.8,208,2014-02-11":{"date":"2014-02-11","time":"00:11.8","score":208,"size":"20x20"},"15x15,00:14.5,249,2014-02-11":{"date":"2014-02-11","time":"00:14.5","score":249,"size":"15x15"},"5x5,00:02.2,40,2014-02-11":{"date":"2014-02-11","time":"00:02.2","score":40,"size":"5x5"},"5x5,00:01.6,40,2014-02-11":{"date":"2014-02-11","time":"00:01.6","score":40,"size":"5x5"},"5x5,00:03.0,59,2014-02-11":{"date":"2014-02-11","time":"00:03.0","score":59,"size":"5x5"},"5x5,00:02.5,35,2014-02-11":{"date":"2014-02-11","time":"00:02.5","score":35,"size":"5x5"},"5x5,00:03.0,80,2014-02-11":{"date":"2014-02-11","time":"00:03.0","score":80,"size":"5x5"},"5x5,00:02.3,39,2014-02-11":{"date":"2014-02-11","time":"00:02.3","score":39,"size":"5x5"},"5x5,00:02.1,40,2014-02-11":{"date":"2014-02-11","time":"00:02.1","score":40,"size":"5x5"},"5x5,00:02.6,50,2014-02-11":{"date":"2014-02-11","time":"00:02.6","score":50,"size":"5x5"}}"