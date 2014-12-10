// /////////////////////////////////////////////////////////////////////////////
/*!	 																	      \n
*			       Lee algorithm - Pathfinding laboratory	      			  \n
*                          by Jiri Klic, Dec 2014							  \n
*																			  \n
*/ /////////////////////////////////////////////////////////////////////////////



#ifndef LEE_H
#define LEE_H

#include <windows.h>
#include <stack>
#include <deque>

#include "../board/board.h"


#define MAX_I 50

struct point
{
	// x,y - coordinates on the board, i - distance
	int x, y, i;

	point(){}
	point(int x_, int y_, int i_)
	{
		x = x_;
		y = y_;
		i = i_;
	}
};



class Lee
{
public:
	Lee();
	void generatePath(point start_, point end_,  Board* board_);
	void drawPath();

private:

	std::stack<point> path_final;
	std::deque<point> wset;
	
	void generateDistances();
	void traceBack();

	bool checkAdjIndex(point tester, int i_);
	void updateAdjSquares(point current);

	point start, end;
	Board* map;

};


#endif LEE_H