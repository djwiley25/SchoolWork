/* globals mazeSolve */
'use strict';

mazeSolveShortestPath = (function(that){

  that.path = [];
  that.visited = {};
  that.originalPath = {};

  that.solve = function () {
    that.path = [];
    that.visited = {};

    solve(that.width-1,that.height-1);

    that.originalPath['' + that.player.x + ',' + that.player.y] = false;
    for(var i in that.path) {
      that.originalPath['' + that.path[i].x + ',' + that.path[i].y] = true;
    }
  };

  function solve(x, y) {
    if(cantMove(x,y)) return false;
    if(solved(x,y)) return true;
    if(alreadyBeenThere(x,y)) return false;

    that.visited['' + x + ',' + y] = true;

    that.path.push({
      x: x,
      y: y
    });

    if(solve(x+1,y) || solve(x-1, y) || solve(x,y+1) || solve(x,y-1))
      return true;

    that.path.pop();
    return false;
  }

  function cantMove(x,y) {
    if(x < 0 || x >= that.width) return true;
    if(y < 0 || y >= that.height) return true;

    if(that.path.length) {
      var prev = {
        x: that.path[that.path.length-1].x,
        y: that.path[that.path.length-1].y
      };

      if(x-prev.x === 1 && that.maze[y][x].walls.left) return true;
      if(prev.x-x === 1 && that.maze[prev.y][prev.x].walls.left) return true;
      if(y-prev.y === 1 && that.maze[y][x].walls.up) return true;
      if(prev.y-y === 1 && that.maze[prev.y][prev.x].walls.up) return true;
    }
    return false;
  }

  function solved(x,y) {
    if(x === that.player.x && y === that.player.y) return true;
  }

  function alreadyBeenThere(x,y) {
    return ('' + x + ',' + y) in that.visited;
  }

}(mazeSolve));