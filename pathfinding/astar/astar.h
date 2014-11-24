/*
#ifndef ASTAR_H
#define ASTAR_H

#include <stack>
#include <queue> 

#include "../node.h"
#include "../board.h"
#include "../gpsa_application.h"

using namespace std;

struct Vector
{
	int x, y, f;

	Vector(){};

	Vector(int a, int b)
	{
		x = a;
		y = b;
	}

	Vector(int a, int b, int c)
	{
		x = a;
		y = b;
		f = c;
	}

	
	// The comparison operator used to order the priority queue.
	// Overloads the operator  >
    bool operator>( const Vector &a ) const {
        return f > a.f;
    }
	
};

extern Board board;

class Astar
{
public:

	void generatePath(Vector start, Vector end);

private:

	std::stack<Vector> path_final;

	// Declare the priority_queue use the replate of cVector, Container of std::vector and greater Compare 
	priority_queue< Vector, vector< Vector >, greater<Vector> > wset;
	

	void generateDistances(Vector start, Vector end);
	void traceBack(Vector start, Vector end);
	void displayPath();

	void updateAdjSquares(Vector point, Vector goal);
	bool isAdjIndex(Vector point, int i);


	int manhattanDistance(Vector point, Vector goal);
	
};

#endif ASTAR_H
*/