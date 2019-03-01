'use strict';

let performance = performance || Date;
let requestAnimationFrame = requestAnimationFrame || function(cb) { setTimeout(function(){cb(Date.now());},0); };

let maze = [[]];
let width = 1;
let height = 1;

let eventQueue = [];

let player = {
    x: 0,
    y: 0
};

let controls = {
    HINT: false,
    BREAD: false,
    SPATH: false,
    SCORE: false,
    OPTIMAL_PATH: false
};

function generateCell(position) {
    var that = {};

    that.position = position;
    that.set = {};
    that.set[that.position] = that;

    that.walls = {
      up: true,
      left: true
    };

    that.sameSet = function(diffCell) {
      return that.position in diffCell.set;
    };

    that.removeWall = function(diffCell) {
      if(that.position - diffCell.positiion > 1) {
        that.walls.up = false;
      } else {
        that.walls.left = false;
      }
    };

    that.unionSet = function(diffCell) {
      var set = that.set;
      var diffSet = diffCell.set;

      for(var i in diffSet) {
        diffSet[i].set = set;
        set[diffSet[i].position] = diffSet[i];
      }
    };

    return that;
}

function randomIter(arr) {
    for(var i in arr) {
      var rand = Math.floor(Math.random() * arr.length);

      var temp = arr[i];
      arr[i] = arr[rand];
      arr[rand] = temp;
    }
}

function generate(w, h) {
    let width = w;
    let height = h;

    let start = performance.now();
    let cellNum = 0;
    let walls = [];

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

    randomIter(walls);

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


let canvas;
let context;
  
let HINT_COL = 'yellow';
let BREAD_COL = 'blue';
let SPATH_COL = 'green';
let OPTIMAL_COL = 'orange';
  
let WALL_COL = 'grey';
  
let PLAYER_COL = 'black';
let PLAYER_FILL_COL = 'white';
  
let END_COL = 'green';
let END_FILL_COL = 'red';
  
let CELL_WIDTH = 25;
let CELL_HEIGHT = CELL_WIDTH;
  
player.width = CELL_WIDTH - 12;
  
function displayTime(timeLbl) {
      $('.maze-timer').text('Time: ' + timeLbl.substr(0,7));
};
  
function showScore() {
      $('.maze-score').text(that.controls.SCORE ? 'Score: ' + that.score : '');
};
  
function checkButtonStatus() {
      if(controls.HINT)  $('#HINT').addClass('active');  else $('#HINT').removeClass('active');
      if(controls.BREAD) $('#BREAD').addClass('active'); else $('#BREAD').removeClass('active');
      if(controls.SPATH)  $('#SPATH').addClass('active');  else $('#SPATH').removeClass('active');
      if(controls.SCORE) $('#SCORE').addClass('active'); else $('#SCORE').removeClass('active');
};
  
function draw(idOrObject) {
    canvas = 'object' === typeof idOrObject ? idOrObject : document.getElementById(idOrObject);
    context = canvas.getContext('2d');
  
    canvas.width = CELL_WIDTH * width;
    canvas.height = CELL_HEIGHT* height;
    context.clearRect(0, 0, canvas.width, canvas.height);
  
    let strokeStyle = context.strokeStyle;
    context.strokeStyle = WALL_COL;
    context.beginPath();
    context.rect(1, 1, canvas.width-2, canvas.height-2);
    context.stroke();
    context.strokeStyle = strokeStyle;
  
    for(let row in maze) {
        for(let col in maze[row]) {
          drawCell(+row, +col, maze[row][col]);
        }
    }
  
    if(controls.BREAD) drawBread();
    if(controls.SPATH) drawPath();
    if(controls.HINT) drawHint();
    if(that.controls.OPTIMAL_PATH) drawOptimalPath();
  
    drawEnd();
  
    drawPlayer();
};
  
function drawCell(row, col, cell) {
    let strokeStyle = context.strokeStyle;
    context.strokeStyle = WALL_COL;
  
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
    let fillStyle = context.fillStyle;
    context.fillStyle = SPATH_COL;
  
    for(let i in path) {
    let col = path[i].x;
    let row = path[i].y;
 
    let x = col * CELL_WIDTH + CELL_WIDTH/2;
    let y = row * CELL_HEIGHT +  CELL_HEIGHT/2;
  
    context.beginPath();
    context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
    context.fill();
    }
    context.fillStyle = fillStyle;
}
  
function drawOptimalPath() {
    let fillStyle = context.fillStyle;
    context.fillStyle = OPTIMAL_COL;
  
    for(let i in originalPath) {
        let coords = i.split(',');
        let col = coords[0];
        let row = coords[1];
  
        let x = col * CELL_WIDTH + CELL_WIDTH/2;
        let y = row * CELL_HEIGHT +  CELL_HEIGHT/2;
  
        context.beginPath();
        context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
        context.fill();
    }
    context.fillStyle = fillStyle;
}
  
function drawHint() {
    if(that.path.length) {
        let fillStyle = context.fillStyle;
        context.fillStyle = HINT_COL;
  
        let col = path[path.length-1].x;
        let row = path[path.length-1].y;
  
        let x = col * CELL_WIDTH + CELL_WIDTH/2;
        let y = row * CELL_HEIGHT +  CELL_HEIGHT/2;
  
        context.beginPath();
        context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
        context.fill();
  
        context.fillStyle = fillStyle;
    }
}
  
function drawBread() {
    if(that.bread.length) {
        let fillStyle = context.fillStyle;
        context.fillStyle = BREAD_COL;
  
        for(let i in bread) {
          let col = bread[i].x;
          let row = bread[i].y;
  
          let x = col * CELL_WIDTH + CELL_WIDTH/2;
          let y = row * CELL_HEIGHT +  CELL_HEIGHT/2;
  
          context.beginPath();
          context.arc(x, y, CELL_WIDTH/4, 0*Math.PI, 2*Math.PI);
          context.fill();
        }
        context.fillStyle = fillStyle;
      }
}
  
function drawEnd() {
    let end = {
    x: that.width-1,
    y: that.height-1
    };
  
    let x = (end.x * CELL_WIDTH) + CELL_WIDTH/2;
    let y = end.y * CELL_HEIGHT + CELL_HEIGHT/2;
  
    let fillStyle = context.fillStyle;
  
    context.beginPath();
    context.arc(x, y, (CELL_WIDTH-20)/2, 0*Math.PI, 2*Math.PI);
    context.strokeStyle = END_COL;
    context.lineWidth = 5;
    context.stroke();
    context.fillStyle = END_FILL_COL;
    context.fill();
  
    context.fillStyle = fillStyle;
}
  
function drawPlayer() {
    let x = (player.x * CELL_WIDTH) + CELL_WIDTH/2;
    let y = (player.y * CELL_HEIGHT) + CELL_HEIGHT/2;
  
    let fillStyle = context.fillStyle;
  
    context.beginPath();
    context.arc(x, y, player.width/2, 0*Math.PI, 2*Math.PI);
    context.strokeStyle = PLAYER_COL;
    context.lineWidth = 5;
    context.stroke();
    context.fillStyle = PLAYER_FILL_COL;
    context.fill();
  
    context.fillStyle = fillStyle;
}

  
  