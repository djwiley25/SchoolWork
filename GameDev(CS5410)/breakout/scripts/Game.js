Breakout.screens['game'] = (function(Keyboard, Paddle, Ball, Scores, Menu, Particles) {
	'use strict';

	let timestamp = performance.now();
	let canvas = document.getElementById('canvas');
	let context = canvas.getContext('2d');

	let lvl, lvlData;
	let bricksDestroyed, rowsDestroyed;
	let speed;
	let rowExtras;
	let topRowReached, shrinkPaddle;
	let paddleLives;
	let balls, maxBalls;
	//Still working on pause/escape
	let pause = false;

	//Countdown that launches nextBall and resets the speed of the ball if needed
	function finalCountdown() {
		let oldSpeedLevel = speed;
		speed = 0;
		Breakout.screens['menu'].countdown();
		window.setTimeout(function() {
			speed = oldSpeedLevel;
			pause = false
		}, 4000);
		window.setTimeout(function() {
			newBall();
			requestAnimationFrame(gameLoop);
		}, 4000);
	}
	//Launch new ball
	function newBall() {
		balls.push(Ball.Ball({
			x: Paddle.getCenter().x,
			y: Paddle.getCenter().y + 2,
			vX: 0,
			vY: -3
		}));
	}
	//Display Score in bottom right
	function showScore(context) {
		context.fillStyle = '#FFFFFF';
		context.font = '16px Arial';
		context.textAlign = 'right';
		context.fillText('Score:', canvas.width - 35, canvas.height - 8);
		context.textAlign = 'left';
		context.fillText(Scores.getScore(), canvas.width - 30, canvas.height - 8);
	}
	//Display paddle lives in bottom left
	function showLives(context) {
		context.fillStyle = '#FFFFFF';
		context.font = '16px Arial';
		context.textAlign = 'right';
		context.fillText('Lives:', 50, canvas.height - 8);

		context.fillStyle = '#FFFFFF';

		for (let i = paddleLives - 1; i >= 0; i--) {
			context.fillRect(55 + (i * 40), canvas.height - 16, 32, 7);
		}
	}

	function update(elapsedTime) {
		Keyboard.update(elapsedTime);
		Breakout.Particles.update(elapsedTime);

		if (maxBalls < (Scores.getScore() / 100)) {
			maxBalls++;
			newBall();
		}

		for (let i = balls.length - 1; i >= 0; i--) {
			for (let j = lvlData.length - 1; j >= 0; j--) {
				lvlData[j].update(elapsedTime, balls[i]);
			}
			Paddle.update(elapsedTime, balls[i]);
			balls[i].update(elapsedTime, canvas, speed);
		}

		let numBricksInRowCrushed = 0;
		rowsDestroyed = 0;
		bricksDestroyed = 0;
		for (let j = 0; j < lvl.height; ++j) {
			numBricksInRowCrushed = 0;
			for (let i = 0; i < lvl.width; ++i) {
				if (j == 0 && lvlData[(j * lvl.width + i)].isDestroyed()) {
					topRowReached = true;
				}
				if (lvlData[(j * lvl.width + i)].isDestroyed()) {
					numBricksInRowCrushed++;
					bricksDestroyed++;
				}
			}
			if (numBricksInRowCrushed >= lvl.width) rowsDestroyed++;
		}
		if (rowsDestroyed > rowExtras) {
			Scores.addPoints(25);
			++rowExtras;
		}
		if (topRowReached && !shrinkPaddle) {
			Paddle.shrinkBy(0.5);
			shrinkPaddle = true;
		}

		if (bricksDestroyed > 4) {
			speed = 1.2;
		}
		if (bricksDestroyed > 12) {
			speed = 1.4;
		}
		if (bricksDestroyed > 36) {
			speed = 1.6;
		}
		if (bricksDestroyed > 62) {
			speed = 2;
		}

		balls = balls.filter(function(element) {
			return !element.dead;
		});

		if (balls.length == 0) {
			--paddleLives;
			pause = true;
			if (paddleLives > 0) {
				finalCountdown();
			}
			else {
				Breakout.Storage.saveScore(Scores.getScore());
				// console.log('saved score ' + Scores.getScore());
				Scores.resetScore();
				Breakout.main.showScreen('menu');
			}
		}

		return;
	}

	function render(elapsedTime) {
		context.clearRect(0, 0, canvas.width, canvas.height);
		Paddle.render(elapsedTime, context);
		Breakout.Particles.render(context);
		for (let i = lvlData.length - 1; i >= 0; i--) {
			lvlData[i].draw(context);
		}
		for (let i = balls.length - 1; i >= 0; i--) {
			balls[i].render(elapsedTime, context);
		}
		showScore(context);
		showLives(context);
	}

	function gameLoop(currentTime) {
		// Compute time since last update
		let elapsedTime = (currentTime - timestamp);
		timestamp = currentTime;

		update(elapsedTime);
		render(elapsedTime);
		// console.log(paused);

		if (!pause) {
			requestAnimationFrame(gameLoop);
		}
		return;
	}

	function run() {
		pause = false;
		requestAnimationFrame(gameLoop);
	}

	function initialize() {
		lvl = Breakout.BrickYard().Level(canvas);
		lvlData = lvl.bricks;
		bricksDestroyed = 0;
		rowsDestroyed = 0;
		speed = 1;
		rowExtras = 0;
		topRowReached = false;
		shrinkPaddle = false;
		paddleLives = 4;
		balls = [];
		maxBalls = 1;
		Paddle.resetSize();

		pause = true;

		context.clearRect(0, 0, canvas.width, canvas.height);
	}

	return {
		initialize: initialize,
		run: run
	}

}(Breakout.KeyboardHandler, Breakout.PaddleLogic, Breakout.BallPit, Breakout.Scoring, Breakout.Menu, 
	Breakout.Particles));