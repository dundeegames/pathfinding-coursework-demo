#ifndef ASTAR_H
#define ASTAR_H

#include "../board/board.h"

#include <iostream>
#include <windows.h>	// Sleep()
#include <stdlib.h>		// abs()
#include <stack>
#include <queue> 




using namespace std;

struct Vector
{
	int x, y, f;

	Vector(){};

	Vector(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	Vector(int x_, int y_, int f_)
	{
		x = x_;
		y = y_;
		f = f_;
	}

	
	// The comparison operator used to order the priority queue.
	// Overloads the operator  >
    bool operator>( const Vector &a ) const {
        return f > a.f;
    }
	
};



class Astar
{
public:

	void generatePath(Vector start, Vector end, Board* board_);

private:

	Board* map;


	std::stack<Vector> path_final;

	// Declare the priority_queue use the replate of cVector, Container of std::vector and greater Compare 
	priority_queue< Vector, vector< Vector >, greater<Vector> > wset;
	

	void generateDistances(Vector start, Vector end);
	void traceBack(Vector start, Vector end);
	void displayPath();

	void updateAdjSquares(Vector point, Vector goal);
	bool isAdjIndex(Vector point, int i_);


	int manhattanDistance(Vector point, Vector goal);
	
};

#endif ASTAR_H
