// Author: Josh Davis
// Last Modified: 12/20/2017
// Purpose: Represents a traversible Node in space

#pragma once

#include <vector>

class Node
{
	// node x, node y
	int nx; int ny;

	float g; // movement cost from start to a node
	float h; // estimated cost for a given node to destination
	float f; // g + h

private:

public:
	//constructors/deconstructors
	Node();
	Node(int tx, int ty, float d, float p);
	~Node();

	//accessers
	int getX();
	int getY();

	float getG();
	void setG(float newg);

	float getH();
	void setH(float newh);

	float getF();
	void setF(float newf);

	void updateHCost(int xDest, int yDest);

	float hCost(int xDest, int yDest);

};