#ifndef BOARD_H
#define BOARD_H

#include "../ui/gui.h"

#include <iostream>
#include <fstream>

using namespace std;


#define BOARD_X 20
#define BOARD_Y 20

#define B_EMPTY 1000
#define B_WALL	999
#define B_START	0
#define B_END	1001


enum MapType {MAP_A, MAP_L};


struct Node
{
	int i;		// index of tile = g, B_EMPTY, B_WALL, B_START, B_END

	int f;		// f costs for pathing
	int g;		// the movement cost to move from the starting point to a given square on the grid, following the path generated to get there
	int h;		// the estimated movement cost to move from that given square on the grid to the final destination

	Node();
	Node(int i_);
	Node(int f_, int g_, int h_, int i_);
};


class Board
{

public:
	Board();
	~Board();


	void init(Gui* ui_, int xpos_, int ypos_);

	void loadMap(char* file_);			// load external map
	void loadMap(MapType type_);		// load internal map

	void setI(int x, int y, int i_);
	void setFGH(int x, int y, int g_, int h_);

	// A* ---------------------
	void drawMap();
	void clearBoard();


	// Lee --------------------
	//void setNode(int x, int y, Node type);
	Node getNode(int x, int y);

private:

	// Lee --------------------
	Node nodeMap[BOARD_X][BOARD_Y];
	int xPosition;
	int yPosition;
	Gui* ui;

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