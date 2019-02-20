#include <time.h>
#include <iostream>

/**
* @brief Check if a winner exists
*
* @param pBoard The board
* @param colSize The column size
* @param rowSize The row size
*
* @return The character of the winner, 0 for no winner, and 't' for a tie
*/
char checkWinner(char** pBoard, int colSize, int rowSize, int winSize)
{
	char index = 0;
	//check horizontally
	for (int i = 0; i < colSize; i++) {
		for (int j = 0; j < rowSize - 3; j++) {
			if (pBoard[i][j] != ' '&&pBoard[i][j] == pBoard[i][j + 1] && pBoard[i][j] == pBoard[i][j + 2] && pBoard[i][j] == pBoard[i][j + 3]) {
				if (pBoard[i][j] == 'p') {
					index = 'p';
				}
				else if (pBoard[i][j] == 'c') {
					index = 'c';
				}
			}
		}
	}
	//check vertically
	for (int i = 0; i < colSize - 3; i++) {
		for (int j = 0; j < rowSize; j++) {
			if (pBoard[i][j] != ' '&&pBoard[i][j] == pBoard[i + 1][j] && pBoard[i][j] == pBoard[i + 2][j] && pBoard[i][j] == pBoard[i + 3][j])
				if (pBoard[i][j] == 'p') {
					index = 'p';
				}
				else if (pBoard[i][j] == 'c') {
					index = 'c';
				}
		}
	}
	//check right diagonal
	for (int i = 0; i < colSize - 3; i++) {
		for (int j = 0; j < rowSize - 3; j++) {
			if (pBoard[i][j] != 0 && pBoard[i][j] == pBoard[i + 1][j + 1] && pBoard[i][j] == pBoard[i + 2][j + 2] && pBoard[i][j] == pBoard[i + 3][j + 3])
				if (pBoard[i][j] == 'p') {
					index = 'p';
				}
				else if (pBoard[i][j] == 'c') {
					index = 'c';
				}

		}
	}
	//check left diagonal
	for (int i = 0; i < colSize - 3; i++) {
		for (int j = 0; j < rowSize - 3; j++) {
			if (pBoard[i][j] != 0 && pBoard[i][j] == pBoard[i + 1][j - 1] && pBoard[i][j] == pBoard[i + 2][j - 2] && pBoard[i][j] == pBoard[i + 3][j - 3])
				if (pBoard[i][j] == 'p') {
					index = 'p';
				}
				else if (pBoard[i][j] == 'c') {
					index = 'c';
				}
		}
	}


	return index;	// TODO
}

/**
* @brief Place a piece onto the board
*
* @param pBoard The game board
* @param colSize The column size
* @param rowSize the row size
* @param columnSelection The column selection
* @param player The players character
*
* @return True if the piece was placed, else false
*/
bool placePiece(char** pBoard, int colSize, int rowSize, int columnSelection, char player)
{
	if (columnSelection >= 0 && columnSelection < colSize) {
		for (int i = rowSize - 1; i >= 0; --i) {
			if (pBoard[i][columnSelection] == ' ') {
				pBoard[i][columnSelection] = player;
				return true;
			}
		}
	}
	return false;
}

/**
* @brief Print out the game board
*
* @param pBoard The game board
* @param colSize The column size
* @param rowSize The row size
*/
void printBoard(char** pBoard, int colSize, int rowSize)
{
	for (int h = 0; h < rowSize+1; h++) {
		std::cout << "|" << h;
	}
	std::cout << "|";
	std::cout << std::endl;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			std::cout << "|" << pBoard[i][j];
			//std::cout << std::endl;
			
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	// TODO
}

int main()
{
	bool running = true;
	printf("Welcome to connect four!\n");
	srand(time(NULL));

	int32_t connectedPiecesToWin = 0;
	int32_t rowSize = 0;
	int32_t colSize = 0;

	// setup game
	std::cout << "How many connected pieces does it take to win?" << std::endl;
	std::cin >> connectedPiecesToWin;

	rowSize = connectedPiecesToWin + 2;
	colSize = connectedPiecesToWin + 3;

	std::cout << "You have selected " << connectedPiecesToWin << " in a row with a game board of " << colSize
		<< " x " << rowSize << std::endl;

	// setup board
	char** pBoard = NULL;

	// TODO create the game board
	pBoard = new char*[rowSize];
	for (int i = 0; i < rowSize; i++) {
		pBoard[i] = new char[colSize];
	}
						  // initialize board
						  // TODO initialize the board
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			pBoard[i][j] = ' ';
		}
	}

						  // play
	char winner = 0;
	char player = 'p';
	do
	{
		int columnChoice = 0;

		do
		{
			if (player == 'p')
			{
				printBoard(pBoard, colSize, rowSize);
				std::cout << "Player's column: ";
				std::cin >> columnChoice;
			}
			else
			{
				// computers turn
				columnChoice = rand() % colSize;
			}
		} while (!placePiece(pBoard, colSize, rowSize, columnChoice, player));

		winner = checkWinner(pBoard, colSize, rowSize, connectedPiecesToWin);
		player = (player == 'c') ? 'p' : 'c';
	} while (running && winner == 0);

	printBoard(pBoard, colSize, rowSize);

	if (winner == 't')
	{
		std::cout << "Too bad, the game was a tie!" << std::endl;
	}
	else if (winner == 'c')
	{
		std::cout << "Oh man, you lost to a computer that randomly places pieces!" << std::endl;
	}
	else
	{
		std::cout << "Congrats! You won!" << std::endl;
	}

	// cleanup
	// TODO cleanup the board

	return 0;
}