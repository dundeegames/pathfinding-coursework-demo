/*
********************************************************************************
*****                                                                      *****
*****                    Hashing - Pathfinding laboratory                  *****
*****                         by Jiri Klic, Dec 2014                       *****
*****                                                                      *****
********************************************************************************
*/



#ifndef HASHING_H
#define HASHING_H


// INCLUDES ////////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>

using std::cout;
using std::endl;



// STURCTURES / ENUMS //////////////////////////////////////////////////////////

enum GameStatus {WIN, loss, draw, undecided, illegal};

// -----------------------------------------------------------------------------

struct  Node
{
	int Node_number;			// Nodes kept in order
	int  dat;
	struct Node * left;    		// doubly-linked    
	struct Node * right;
};

// -----------------------------------------------------------------------------

struct position
{
	int bd[3][3];
	GameStatus game;
	int npieces;
};

// -----------------------------------------------------------------------------

typedef  struct  Node*  pointer;



// CLASS ///////////////////////////////////////////////////////////////////////

class Hashing
{

public:
	Hashing();
	~Hashing();

	void run();


private:
	position wset[800], dlist[8000];
	//position temp;					// used to initialise data structures
	int head, rear, dlist1;
	bool hashtable[20000];


	void check_wset();
	void  insert(int v, int num, Node* h);
	int boardval(int b[3][3]);
	int min_boardval(position p);
	void single_step();

	int search_dlist(position p);
	GameStatus is_win_or_draw(position p, int xo);
	int is_duplicate(int p[3][3], int q[3][3]);
	void swap(int &a, int &b);
	void rotation(int b[3][3]);

	void reflection(int b[3][3]);
	void print_status();
	void add_to_wset(position p);
	int wset_not_empty();			// looks more like bool
	position get_from_wset();

	void add_to_dlist(position p);
	void printp(position p);
	void printg(GameStatus gg);


};

#endif // HASHING_H