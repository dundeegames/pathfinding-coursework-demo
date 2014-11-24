/*
#ifndef LEE_H
#define LEE_H

#include <windows.h>
#include <stack>
#include <deque>

#include "../board.h"

extern Board board;

#define MAX_I 50

struct point
{
	// x,y - coordinates on the board, i - distance
	int x, y, i;

	point(){}
	point(int a, int b, int c)
	{
		x = a;
		y = b;
		i = c;
	}
};



class Lee
{
public:
	Lee();
	void generatePath(point s, point e);
	void drawPath();

private:

	std::stack<point> path_final;
	std::deque<point> wset;
	
	void generateDistances();
	void traceBack();

	bool checkAdjIndex(point tester, int index);
	void updateAdjSquares(point current);

	point start, end;
};


#endif LEE_H
*/