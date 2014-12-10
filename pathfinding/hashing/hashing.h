// /////////////////////////////////////////////////////////////////////////////
/*!	 																	      \n
*			          Hashing - Pathfinding laboratory	         			  \n
*                          by Jiri Klic, Dec 2014							  \n
*																			  \n
*/ /////////////////////////////////////////////////////////////////////////////




#ifndef HASHING_H
#define HASHING_H


// INCLUDES ////////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>
#include "../ui/gui.h"
#include "../test/profiler.h"

using std::cout;
using std::endl;

#define HASH_MAX 20000
#define WSET_MAX 800
#define DLIST_MAX 8000
#define BD_SIZE 3

#define COUNTER 18

#define TABLE_X 13
#define TABLE_Y 23
#define DIST_X 20
#define DIST_Y 12

// STURCTURES / ENUMS //////////////////////////////////////////////////////////

enum GameStatus {WIN, LOSS, DRAW, UNDECIDED, ILLEGAL};

// -----------------------------------------------------------------------------

struct  Piece
{
	Piece(){}
	int Piece_number;			// Pieces kept in order
	int dat;
	struct Piece * left;    		// doubly-linked    
	struct Piece * right;
};

// -----------------------------------------------------------------------------

struct Position
{
	int bd[BD_SIZE][BD_SIZE];
	GameStatus game;
	int npieces;
};

// -----------------------------------------------------------------------------

/*
* Original piece of code. If all pieces renamed to Piece*, it will break the
* the code. Since Piece is strunct and not Class, I asume the problem is somwhere
* there. Dynamic memory allocation new and malloc works interchangably.
*/
typedef  struct  Piece*  pointer;



// CLASS ///////////////////////////////////////////////////////////////////////

class Hashing
{

public:
	Hashing(Gui* ui_);
	~Hashing();


	void run();


private:
	Gui* ui;
	int funcCounter[COUNTER];
	int resultCounter[5];
	int xoffset;
	int yoffset;

	Profiler profiler;


	Position wset[WSET_MAX], dlist[DLIST_MAX];
	//Position temp;					// used to initialise data structures
	int head, rear, dlist1;
	bool hashtable[HASH_MAX];


	void drawTables(int x, int y);

	// system functions (from original code)
	void check_wset();
	void  insert(int v, int num, Piece* h);
	int boardval(int b[BD_SIZE][BD_SIZE]);
	int min_boardval(Position p);
	void single_step();

	int search_dlist(Position p);
	GameStatus is_win_or_draw(Position p, int xo);
	int is_duplicate(int p[BD_SIZE][BD_SIZE], int q[BD_SIZE][BD_SIZE]);
	void swap(int &a, int &b);
	void rotation(int b[BD_SIZE][BD_SIZE]);

	void reflection(int b[BD_SIZE][BD_SIZE]);
	void print_status();
	void add_to_wset(Position p);
	int wset_not_empty();			// looks more like bool
	Position get_from_wset();

	void add_to_dlist(Position p);
	void printp(Position p);
	void printg(GameStatus gg);


};

#endif // HASHING_H