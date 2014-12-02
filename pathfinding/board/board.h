#ifndef BOARD_H
#define BOARD_H

#include "../ui/gui.h"
#include "node.h"

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

	int getI(int x, int y);
	int getF(int x, int y);
	int getH(int x, int y);

	void updateData(int nodes_, int size_);
	void drawMap();
	void drawIndex(int x, int y, int i_);
	void clearBoard();

	Node getNode(int x, int y);


private:
	int sizeNcur;	// Current and Max size of wset in Numer of nodes
	int sizeNmax;
	int sizeBcur;	// Current and Max size of wset in Bytes
	int sizeBmax;

	void drawData();	// displays values of cur and max wset

	// Lee --------------------
	Node nodeMap[BOARD_X][BOARD_Y];
	int xPosition;
	int yPosition;
	Gui* ui;

};

#endif BOARD_H