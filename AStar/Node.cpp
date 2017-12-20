// Author: Josh Davis
// Last Modified: 12/20/2017
// Purpose: Represents a traversible Node in space

#include "Node.h";

Node::Node() 
{
	nx = 0; ny = 0;
	g = 0.0;
	h = 0.0;
};

Node::Node(int tx, int ty, double d, double p)
{
	//curLoc.x = l.x; curLoc.y = l.y; curLoc.z = l.z;
	nx = tx; ny = ty;
	g = d;
	h = p;
}

Node::~Node()
{

}

int Node::getX() { return nx; }
int Node::getY() { return ny; }

double Node::getG() { return g; }
void Node::setG(double value) { g = value; }

double Node::getH() { return h; }
void Node::setH(double value) { h = value; }

double Node::getF() { return f; }
void Node::setF(double value) { f = value; }

void Node::updateHCost(int xDest, int yDest)
{
	f = g + hCost(xDest, yDest);
}

//process movement cost
void Node::gCost(int i) // i: direction
{
	g += (i % 2 == 0 ? 10 : 14);
}

//estimate h cost (cost to end of maze) 
double Node::hCost(int xDest, int yDest)
{
	int xd, yd;
	xd = xDest - nx;
	yd = yDest - ny;

	//Euclidian distance
	h = (sqrt(xd*xd + yd*yd));

	return(h);
}