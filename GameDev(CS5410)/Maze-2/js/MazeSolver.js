/* globals console, performance */
'use strict';
var performance = performance || Date;
var requestAnimationFrame = requestAnimationFrame || function(cb) { setTimeout(function(){cb(Date.now());},0); };

var MazeSolver = (function(){

  var that = {};

  that.maze = [[]];
  that.width = 1;
  that.height = 1;

  that.eventQueue = [];

  that.player = {
    x: 0,
    y: 0
  };

  that.controls = {
    HINT: false,
    BREAD: false,
    PATH: false,
    SCORE: false,
    OPTIMAL_PATH: false
  };

  function createCell(location) {
    var that = {};

    that.location = location;
    that.set = {};
    that.set[that.location] = that;

    that.walls = {
      up: true,
      left: true
    };

    that.sameSet = function(otherCell) {
      return that.location in otherCell.set;
    };

    that.removeWall = function(otherCell) {
      if(that.location - otherCell.location > 1) {
        that.walls.up = false;
      } else {
        that.walls.left = false;
      }
    };

    that.unionSet = function(otherCell) {
      var set = that.set;
      var otherSet = otherCell.set;

      for(var i in otherSet) {
        otherSet[i].set = set;
        set[otherSet[i].location] = otherSet[i];
      }
    };

    return that;
  }

  function shuffle(arr) {
    for(var i in arr) {
      var rand = Math.floor(Math.random() * arr.length);

      var temp = arr[i];
      arr[i] = arr[rand];
      arr[rand] = temp;
    }
  }

  that.generate = function(w, h) {
    that.width = w;
    that.height = h;
    that.maze.length = 0;

    var start = performance.now();
    var cellNum = 0;
    var walls = [];

    for(var row = 0; row < h; row++) {
      that.maze[row] = [];
      for(var col = 0; col < w; col++) {
        that.maze[row][col] = createCell(cellNum);

        if(cellNum % w !== 0) {
          walls.push({
            currCell: that.maze[row][col],
            prevCell: that.maze[row][col-1]
          });
        }
        if(cellNum >= w) {
          walls.push({
            currCell: that.maze[row][col],
            prevCell: that.maze[row-1][col],
          });
        }

        cellNum++;
      }
    }

    shuffle(walls);

    console.log('make', performance.now() - start);

    for(var i in walls) {
      var currCell = walls[i].currCell;
      var prevCell = walls[i].prevCell;

      if(!currCell.sameSet(prevCell)) {
        currCell.removeWall(prevCell);
        currCell.unionSet(prevCell);
      }
    }

    console.log('generate', performance.now() - start);
  };

  return that;

}());