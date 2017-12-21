// Author: Josh Davis
// Last Modified: 12/20/2017
// Purpose: Represents a traversible Node in space

#include "Node.h";

Node::Node() 
{
	nx = 0; ny = 0;
	g = 0.0f;
	h = 0.0f;
	f = FLT_MAX;
};

Node::Node(int tx, int ty, float d, float p)
{
	//curLoc.x = l.x; curLoc.y = l.y; curLoc.z = l.z;
	nx = tx; ny = ty;
	g = d;
	h = p;
	f = FLT_MAX;
}

Node::~Node()
{

}

int Node::getX() { return nx; }
int Node::getY() { return ny; }

float Node::getG() { return g; }
void Node::setG(float value) { g = value; }

float Node::getH() { return h; }
void Node::setH(float value) { h = value; }

float Node::getF() { return f; }
void Node::setF(float value) { f = value; }

//estimate h cost (cost to end of maze) 
float Node::hCost(int xDest, int yDest)
{
	//switched to Manhattan because it makes more sense for a maze like this
	//Manhattan distance
	h = abs(nx - xDest) + abs(ny - yDest);

	return(h);
}