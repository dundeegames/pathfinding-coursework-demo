#include"node.h"

Node::Node()
{

}

// i - 
Node::Node(int a, int b, int c, int d)
{
	i = a;
	f = b;
	g = c;
	h = d;
}

Node::Node(int a)
{
	i = a;
}

void Node::setI(int a)
{
	i = a;
}

void Node::setFGH(int a, int b)
{
	f = a + b;
	g = a;
	h = b;

	i = g;
}

int Node::getI()
{
	return i;
}

int Node::getF()
{
	return f;
}

int Node::getH()
{
	return h;
}