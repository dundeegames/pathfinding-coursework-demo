///*****************************************************************************
///*****************************************************************************
///*****                                                                   *****
///*****                  Hashing - Pathfinding laboratory                 *****
///*****                       by Jiri Klic, Dec 2014                      *****
///*****                                                                   *****
///*****************************************************************************
///*****************************************************************************



#ifndef HASHING_H
#define HASHING_H


// INCLUDES ////////////////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>

using std::cout;
using std::endl;

#define HASH_MAX 20000
#define WSET_MAX 800
#define DLIST_MAX 8000
#define BD_SIZE 3

// STURCTURES / ENUMS //////////////////////////////////////////////////////////

enum GameStatus {WIN, loss, draw, undecided, illegal};

// -----------------------------------------------------------------------------

struct  Node
{
	int Node_number;			// Nodes kept in order
	int dat;
	struct Node * left;    		// doubly-linked    
	struct Node * right;
};

// -----------------------------------------------------------------------------

struct Position
{
	int bd[BD_SIZE][BD_SIZE];
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
	Position wset[WSET_MAX], dlist[DLIST_MAX];
	//Position temp;					// used to initialise data structures
	int head, rear, dlist1;
	bool hashtable[HASH_MAX];


	void check_wset();
	void  insert(int v, int num, Node* h);
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