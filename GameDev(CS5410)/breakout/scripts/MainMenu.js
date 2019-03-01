Breakout.screens['menu'] = (function() {
	'use strict';

	var that = {};
	var timestamp = performance.now();

	var menuOptions;
	var selectedOption;
	var menuCanvas = document.getElementById('menu');
	var menuContext = menuCanvas.getContext('2d');
	var pause, skippy;

	var timeOut = [];

	that.getContext = function() {
		return menuContext;
	}

	that.initialize = function() {
		menuOptions = 0;
		selectedOption = 0;
		pause = true;
		skippy = false;

		// console.log('initializing main menu');
		menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height);
	}

	that.run = function() {
		pause = false;
		skippy = false;
		// console.log('running main menu');
		that.showMainMenu();
		// requestAnimationFrame(menuLoop);
	}

	function menuUp() {
		// console.log('asdfasdfasdfup');
		if (selectedOption > 0) {
			--selectedOption;
			Breakout.KeyboardHandler.unregisterCommand(KeyEvent.DOM_VK_UP);
			timeOut.push(window.setTimeout(function() {
				Breakout.KeyboardHandler.registerCommand(KeyEvent.DOM_VK_UP, menuUp);
			}, 200));

		}
	}

	function menuDown() {
		// console.log('down');
		if (selectedOption < menuOptions.length - 1) {
			++selectedOption;
			Breakout.KeyboardHandler.unregisterCommand(KeyEvent.DOM_VK_DOWN);
			timeOut.push(window.setTimeout(function() {
				Breakout.KeyboardHandler.registerCommand(KeyEvent.DOM_VK_DOWN, menuDown);
			}, 200));
		}
	}

	function menuSelect() {
		menuOptions[selectedOption]();
		Breakout.KeyboardHandler.unregisterCommand(KeyEvent.DOM_VK_RETURN);
		timeOut.push(window.setTimeout(function() {
			Breakout.KeyboardHandler.registerCommand(KeyEvent.DOM_VK_RETURN, menuSelect);
		}, 500));
	}

	function newGame() {
		pause = true;
		menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height);
		for (var i = timeOut.length - 1; i >= 0; i--) {
			window.clearTimeout(timeOut[i]);
		}
		Breakout.KeyboardHandler.unregisterCommand(KeyEvent.DOM_VK_UP);
		Breakout.KeyboardHandler.unregisterCommand(KeyEvent.DOM_VK_DOWN);
		Breakout.KeyboardHandler.unregisterCommand(KeyEvent.DOM_VK_RETURN);
		Breakout.screens['game'].initialize();
		Breakout.main.showScreen('game');
	}

	function highScores() {
		var scores = Breakout.Storage.getHighScores();
		menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#000000';
		menuContext.fillRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#f44242';
		menuContext.textAlign = 'center';
		menuContext.font = '72px Courier New';
		menuContext.fillText("High Scores", menuCanvas.width / 2, menuCanvas.height / 4);
		menuContext.textAlign = 'left';
		menuContext.font = '24px Courier New';
		for (var i = 0; i < scores.length; ++i) {
			menuContext.fillText((i + 1) + '. ' + scores[i], menuCanvas.width / 2 - 50, 150 + i * 20);
		}
		menuContext.font = '24px Courier New';
		menuContext.textAlign = 'left';
		menuContext.fillText("Back", menuCanvas.width / 2 - 20, 280);

		selectedOption = 0;
		menuOptions = [that.run];

		requestAnimationFrame(menuLoop);	}

	function credits() {
		menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#000000';
		menuContext.fillRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#f44242';
		menuContext.textAlign = 'center';
		menuContext.font = '72px Courier New';
		menuContext.fillText("Breakout", menuCanvas.width / 2, menuCanvas.height / 4);
		menuContext.font = '24px Courier New';
		menuContext.fillText("DJ Wiley", menuCanvas.width / 2, 
			menuCanvas.height / 2);
		menuContext.textAlign = 'left';
		menuContext.fillText("Back", menuCanvas.width / 2 - 20, 280);

		selectedOption = 0;
		menuOptions = [that.run];

		requestAnimationFrame(menuLoop);
	}

	that.escape = function() {
		menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#000000';
		menuContext.fillRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#f44242';
		menuContext.textAlign = 'center';
		menuContext.font = '72px Courier New';
		menuContext.fillText("Breakout", menuCanvas.width / 2, menuCanvas.height / 4);
		menuContext.font = '24px Courier New';
		menuContext.fillText("DJ Wiley", menuCanvas.width / 2, 
			menuCanvas.height / 2);
		menuContext.textAlign = 'left';
		menuContext.fillText("Resume", menuCanvas.width / 2 - 20, 280);
		menuContext.fillText("Quit", menuCanvas.width / 2 - 20, 320);

		selectedOption = 0;
		menuOptions = [runGame, that.run];

		requestAnimationFrame(menuLoop);
	}

	function runGame() {
		Breakout.main.showScreen('game');
	}

	function update(elapsedTime) {
		Breakout.KeyboardHandler.update(elapsedTime);
	}

	function render() {
		menuContext.clearRect(0, 240, menuCanvas.width / 2 - 25, menuCanvas.height);
		menuContext.fillStyle = '#f44242';
		menuContext.fillText('>', menuCanvas.width / 2 - 45, 280 + (40 * selectedOption));
	}

	function menuLoop(currentTime) {
		var elapsedTime = (currentTime - timestamp);
		timestamp = currentTime;

		update(elapsedTime);
		if (!skippy) {
			render();
		}

		if (!pause) {
			requestAnimationFrame(menuLoop);
		}
	}

	that.showMainMenu = function() {
		menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#000000';
		menuContext.fillRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#f44242';
		menuContext.textAlign = 'center';
		menuContext.font = '72px Courier New';
		menuContext.fillText("Breakout", menuCanvas.width / 2, menuCanvas.height / 4);
		menuContext.font = '24px Courier New';
		menuContext.textAlign = 'left';
		menuContext.fillText("New Game", menuCanvas.width / 2 - 20, 280);
		menuContext.fillText("High Scores", menuCanvas.width / 2 - 20, 320);
		menuContext.fillText("Credits", menuCanvas.width / 2 - 20, 360);

		menuOptions = [newGame, highScores, credits];
		selectedOption = 0;

		Breakout.KeyboardHandler.registerCommand(KeyEvent.DOM_VK_UP, menuUp);
		Breakout.KeyboardHandler.registerCommand(KeyEvent.DOM_VK_DOWN, menuDown);
		Breakout.KeyboardHandler.registerCommand(KeyEvent.DOM_VK_RETURN, menuSelect);

		requestAnimationFrame(menuLoop);
	}

	that.countdown = function() {
		menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height);
		menuContext.fillStyle = '#f44242';
		menuContext.font = '74px Courier New';
		menuContext.textAlign = 'center';
		window.setTimeout(function() {
			menuContext.fillText('3', canvas.width / 2, canvas.height / 2)
		}, 1000);
		window.setTimeout(function() {
			menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height)
		}, 1900);
		window.setTimeout(function() {
			menuContext.fillText('2', canvas.width / 2, canvas.height / 2)
		}, 2000);
		window.setTimeout(function() {
			menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height)
		}, 2900);
		window.setTimeout(function() {
			menuContext.fillText('1', canvas.width / 2, canvas.height / 2)
		}, 3000);
		window.setTimeout(function() {
			menuContext.clearRect(0, 0, menuCanvas.width, menuCanvas.height)
		}, 3900);
	}

	return that;
}());