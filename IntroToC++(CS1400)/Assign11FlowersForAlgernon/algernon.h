#ifndef ALGERNON_H
#define ALGERNON_H


const int ROWS = 20;
const int COLS = 40;

enum Thing { space, wall, flower, start, cheese, U, D, L, R };

// Write a function
//
//    void algernon(...)
//
// that finds the shortest path in a maze represented
// by a 2D array of Things (where spaces represent
// potential paths, walls can never be paths, and
// flowers mark the solution path). Also in the maze
// is a single start element and a single cheese
// element. Lastly, you can temporarily set elements
// of the maze to U, D, L, or R to aid in your task,
// but those should be removed and set to something 
// else before returning.
//
// No diagonal moves are allowed; only up, down, left,
// and right.
//
// In your function, you are given a static 2D array
// of Things called maze[ROWS][COLS].  The initial
// maze has only spaces, walls, a single start element,
// and a single cheese element -- no flowers. 
//
// Additionally, all array elements around the perimeter
// are guaranteed to be constructed solely of walls.
//
// Your function should replace each space element
// along the shortest path from start to cheese with
// a flower and then return.
//
// If no path exists, the maze is to remain unaltered.
// 
// Please make good use of functions, comments, and 
// indentation to keep your code easily readable.  No
// errors or warnings when compiling.
//
// What to turn in: algernon.cpp and nothing else.

void algernon(Thing maze[ROWS][COLS]);

#endif