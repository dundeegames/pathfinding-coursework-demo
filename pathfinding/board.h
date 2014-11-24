#ifndef BOARD_H
#define BOARD_H

#include"node.h"

#define BOARD_X 20
#define BOARD_Y 20

#define B_EMPTY 1000
#define B_WALL	999
#define B_START	0
#define B_END	1001


class Board
{

public:
	Board();
	~Board();

	// A* ---------------------
	void draw();
	void clearBoard();
	Node board[BOARD_X][BOARD_Y];


	// Lee --------------------
	void setSquare(int x, int y, int type);
	int getSquare(int x, int y);
	void clearPathing();

private:

	// Lee --------------------
	int intBoard[BOARD_X][BOARD_Y];


};

#endif BOARD_H


/*
// Lee

class cBoard
{
public:
	void setSquare(int x, int y, int type);
	int getSquare(int x, int y);

	void clearPathing();

private:
	int board[BOARD_X][BOARD_Y];
};

*/