#ifndef NODE_H
#define NODE_H

class Node
{
public:
	
	Node();
	Node(int a);
	Node(int a, int b, int c, int d);

	void setI(int a);
	void setFGH(int a, int b);

	int getI();
	int getF();
	int getH();

private:

	int i;			// index of tile

	int f, g, h;	// f/g/h costs for pathing
	

};

#endif NODE_H