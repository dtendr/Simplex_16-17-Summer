// Author: Josh Davis
// Last Modified: 12/20/2017
// Purpose: Represents a traversible Node in space

#pragma once

#include <vector>

class Node
{
	// node x, node y
	int nx; int ny;

	double g; // movement cost from start to a node
	double h; // estimated cost for a given node to destination
	double f; // g + h

private:

public:
	//constructors/deconstructors
	Node();
	Node(int tx, int ty, double d, double p);
	~Node();

	//accessers
	int getX();
	int getY();

	double getG();
	void setG(double newg);

	double getH();
	void setH(double newh);

	double getF();
	void setF(double newf);

	void updateHCost(int xDest, int yDest);

	void gCost(int i);

	double hCost(int xDest, int yDest);

};