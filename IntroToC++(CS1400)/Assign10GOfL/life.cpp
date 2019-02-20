#include <iostream>
#include "life.h"

using namespace std;

int liveNeighbor(const bool current[ROWS][COLS], int row, int col)
{
	int neighbors = 0;

	if (current[row][col] == true)
	{


		for (int i = -1; row + i <= row + 1; i++)
		{
			for (int c = -1;col + c <= col + 1;c++)
			{
				if (i == 0 && c == 0 || row + i < 0 || row + i < ROWS || col + c<0 || col + c>ROWS)
				{

				}

				else if (current[row + i][col + c] == true)
					neighbors++;
			}
		}
	}

	return neighbors;
}
int deadNeighbor(const bool current[ROWS][COLS], int row, int col)
{
	int neighbors2 = 0;

	if (current[row][col] == true)
	{


		for (int i = -1; row + i <= row + 1; i++)
		{
			for (int c = -1;col + c <= col + 1;c++)
			{
				if (i == 0 && c == 0 || row + i<0 || row + i<ROWS || col + c<0 || col + c>ROWS)
				{

				}

				else if (current[row + i][col + c] == true)
					neighbors2++;
			}
		}
	}
	return neighbors2;

}
void life(const bool current[ROWS][COLS], bool next[ROWS][COLS]) {
	int neighbors = 0, neighbors2 = 0;
	for (int row = 0;row < ROWS;row++)
	{
		for (int col = 0;col < ROWS;col++)
		{
			neighbors = liveNeighbor(current, row, col);
			if (neighbors <= 1)
				next[row][col] = false;
			if (neighbors == 2 || neighbors == 3)
				next[row][col] = true;
			if (neighbors>=4)
				next[row][col] = false;

		}
	}

	for (int row = 0;row < ROWS;row++)
	{
		for (int col = 0;col < ROWS;col++)
		{
			neighbors2 = deadNeighbor(current, row, col);
			if (neighbors2 == 3)
				next[row][col] = true;
		}
	}
}
