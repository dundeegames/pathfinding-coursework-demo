#ifndef NODE_H
#define NODE_H

class Node
{
public:
	
	Node();
	Node(int f_, int g_, int h_, int i_);

	void init(int if_);
	void setI(int i_);
	void setFGH(int g_, int h_);

	int getI();
	int getF();
	int getH();

private:

	int i;		// index of tile = g, B_EMPTY, B_WALL, B_START, B_END

	int f;		// f costs for pathing
	int g;		// the movement cost to move from the starting point to a given square on the grid, following the path generated to get there
	int h;		// the estimated movement cost to move from that given square on the grid to the final destination
	

};


#endif NODE_H