// Author: Josh Davis
// Last Modified: 12/19/2017
// Purpose: Generates maze data and solves using A*

#pragma once

#include <vector>
#include <time.h>
#include <list>

struct Node
{
	// node x, node y
	int nx; int ny;

	int g; // movement cost from start to a node
	int h; // estimated cost for a given node to destination
	int f; // g + h

public:

	Node() {

	};

	Node(int tx, int ty, int d, int p)
	{
		//curLoc.x = l.x; curLoc.y = l.y; curLoc.z = l.z;
		nx = tx; ny= ty;
		g = d; 
		h = p;
	}

	~Node() {

	}

	int getX() { return nx; }
	int getY() { return ny; }

	int getG() { return g; }
	int getH() { return h; }

	int getF() { return f; }

	void updateHCost(int & xDest, int & yDest)
	{
		f = g + hCost(xDest, yDest);
	}

	//process movement cost
	void gCost(int & i) // i: direction
	{
		g += (i % 2 == 0 ? 10 : 14);
	}

	//estimate h cost (cost to end of maze) 
	int & hCost(int & xDest, int & yDest)
	{
		int xd, yd;
		xd = xDest - nx;
		yd = yDest - ny;

		//Euclidian distance
		h = (sqrt(xd*xd + yd*yd));

		return(h);
	}
};

class Maze
{
	int default_maze_size_x = 80;
	int default_maze_size_y = 25;

private:
	//nodes that exist
	std::vector < std::vector < Node* > > nodes;

	//walls of the maze
	std::vector < std::vector < bool > > walls;

	//A* open and closed lists
	std::vector<Node*> OPEN;
	std::vector<Node*> CLOSED;

public:
	//constructors/deconstructors
	Maze();
	Maze(int w, int h);
	~Maze();

	//Maze data accessers
	int MazeX();
	int MazeY();
	std::vector < std::vector < bool > > MazeMap();

	//A* methods
	bool isAllowable(int x, int y);
	bool isDone(std::pair<int, int>, int x, int y);
	void AStar(std::pair<int,int> a, std::pair<int,int> b);
	void CheckSuccessor(int x, int y)
};