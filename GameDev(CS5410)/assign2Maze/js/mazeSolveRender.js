/* globals mazeSolve */
'use strict';

(function (that) {
  var canvas;
  var context;

  var HINT_COLOR = 'yellow';
  var BREAD_COLOR = 'red';
  var PATH_COLOR = 'green';
  var OPTIMAL_PATH_COLOR = 'orange';

  var WALL_COLOR = 'black';

  var PLAYER_STROKE_COLOR = 'black';
  var PLAYER_FILL_COLOR = 'gray';

  var END_STROKE_COLOR = 'green';
  var END_FILL_COLOR = 'lime';

  var CELL_WIDTH = 25;
  var CELL_HEIGHT = CELL_WIDTH;

  that.player.width = CELL_WIDTH - 12;

  that.showTime = function(timeLabel) {
    $('.maze-timer').text('Time: ' + timeLabel.substr(0,7));
  };

  that.showScore = function() {
    $('.maze-score').text(that.controls.SCORE ? 'Score: ' + that.score : '');
  };

  that.checkButtonStatus = function() {
    if(that.controls.HINT)  $('#HINT').addClass('active');  else $('#HINT').removeClass('active');
    if(that.controls.BREAD) $('#BREAD').addClass('active'); else $('#BREAD').removeClass('active');
    if(that.controls.PATH)  $('#PATH').addClass('active');  else $('#PATH').removeClass('active');
    if(that.controls.SCORE) $('#SCORE').addClass('active'); else $('#SCORE').removeClass('active');
  };

  that.draw = function(idOrObject) {
    canvas = 'object' === typeof idOrObject ? idOrObject : document.getElementById(idOrObject);
    context = canvas.getContext('2d');

    canvas.width = CELL_WIDTH * that.width;
    canvas.height = CELL_HEIGHT* that.height;
    context.clearRect(0, 0, canvas.width, canvas.height);

    var strokeStyle = context.strokeStyle;
    context.strokeStyle = WALL_COLOR;
    context.beginPath();
    context.rect(1, 1, canvas.width-2, canvas.height-2);
    context.stroke();
    context.strokeStyle = strokeStyle;

    for(var row in that.maze) {
      for(var col in that.maze[row]) {
        drawCell(+row, +col, that.maze[row][col]);
      }
    }

    if(that.controls.BREAD) drawBread();
    if(that.controls.PATH) drawPath();
    if(that.controls.HINT) drawHint();
    if(that.controls.OPTIMAL_PATH) drawOptimalPath();

    drawEnd();

    drawPlayer();
  };

  function drawCell(row, col, cell) {
    var strokeStyle = context.strokeStyle;
    context.strokeStyle = WALL_COLOR;

    if(cell.walls.up) {
      context.beginPath();
      context.moveTo(col * CELL_WIDTH, row * CELL_HEIGHT);
      context.lineTo((col+1) * CELL_WIDTH, row * CELL_HEIGHT);
      context.stroke();
    }
    if(cell.walls.left) {
      context.beginPath();
      context.moveTo(col * CELL_WIDTH, row * CELL_HEIGHT);
      context.lineTo(col * CELL_WIDTH, (row+1) * CELL_HEIGHT);
      context.stroke();
    }
    context.strokeStyle = strokeStyle;
  }

  function drawPath() {
    var fillStyle = context.fillStyle;
    context.fillStyle = PATH_COLOR;

    for(var i in that.path) {
      var col = that.path[i].x;
      var row = that.path[i].y;

      var x = col * CELL_WIDTH + CELL_WIDTH/2;
      var y = row * CELL_HEIGHT +  CELL_HEIGHT/2;

      context.beginPath();
      context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
      context.fill();
    }
    context.fillStyle = fillStyle;
  }

  function drawOptimalPath() {
    var fillStyle = context.fillStyle;
    context.fillStyle = OPTIMAL_PATH_COLOR;

    for(var i in that.originalPath) {
      var coords = i.split(',');
      var col = coords[0];
      var row = coords[1];

      var x = col * CELL_WIDTH + CELL_WIDTH/2;
      var y = row * CELL_HEIGHT +  CELL_HEIGHT/2;

      context.beginPath();
      context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
      context.fill();
    }
    context.fillStyle = fillStyle;
  }

  function drawHint() {
    if(that.path.length) {
      var fillStyle = context.fillStyle;
      context.fillStyle = HINT_COLOR;

      var col = that.path[that.path.length-1].x;
      var row = that.path[that.path.length-1].y;

      var x = col * CELL_WIDTH + CELL_WIDTH/2;
      var y = row * CELL_HEIGHT +  CELL_HEIGHT/2;

      context.beginPath();
      context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
      context.fill();

      context.fillStyle = fillStyle;
    }
  }

  function drawBread() {
    if(that.bread.length) {
      var fillStyle = context.fillStyle;
      context.fillStyle = BREAD_COLOR;

      for(var i in that.bread) {
        var col = that.bread[i].x;
        var row = that.bread[i].y;

        var x = col * CELL_WIDTH + CELL_WIDTH/2;
        var y = row * CELL_HEIGHT +  CELL_HEIGHT/2;

        context.beginPath();
        context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
        context.fill();
      }
      context.fillStyle = fillStyle;
    }
  }

  function drawEnd() {
    var end = {
      x: that.width-1,
      y: that.height-1
    };

    var x = (end.x * CELL_WIDTH) + CELL_WIDTH/2;
    var y = end.y * CELL_HEIGHT + CELL_HEIGHT/2;

    var fillStyle = context.fillStyle;

    context.beginPath();
    context.arc(x, y, (CELL_WIDTH-20)/2, 0*Math.PI, 2*Math.PI);
    context.strokeStyle = END_STROKE_COLOR;
    context.lineWidth = 5;
    context.stroke();
    context.fillStyle = END_FILL_COLOR;
    context.fill();

    context.fillStyle = fillStyle;
  }

  function drawPlayer() {
    var x = (that.player.x * CELL_WIDTH) + CELL_WIDTH/2;
    var y = that.player.y * CELL_HEIGHT + CELL_HEIGHT/2;

    var fillStyle = context.fillStyle;

    context.beginPath();
    context.arc(x, y, that.player.width/2, 0*Math.PI, 2*Math.PI);
    context.strokeStyle = PLAYER_STROKE_COLOR;
    context.lineWidth = 5;
    context.stroke();
    context.fillStyle = PLAYER_FILL_COLOR;
    context.fill();

    context.fillStyle = fillStyle;
  }

}(mazeSolve));ß