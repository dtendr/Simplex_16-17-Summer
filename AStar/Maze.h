// Author: Josh Davis
// Last Modified: 12/20/2017
// Purpose: Generates maze data and solves using A*

#pragma once

#include <vector>
#include <time.h>
#include <list>

#include "Node.h"


class Maze
{
	int default_maze_size_x = 25;
	int default_maze_size_y = 25;

	//entrance marked, exit marked respectively
	bool enM;
	bool exM;

private:
	//nodes that exist
	std::vector < std::vector < Node* > > nodes;

	//walls of the maze
	std::vector < std::vector < bool > > walls;

	//A* open and closed lists
	//OPEN contains Nodes to reference x,y and f
	//for CLOSED, really doesn't matter
	std::vector< Node* > OPEN;
	std::vector< std::vector < bool > > CLOSED;

	//the resultant solution path from A*
	std::vector < std::vector < bool > > path;

public:
	//constructors/deconstructors
	Maze();
	Maze(int w, int h);
	~Maze();

	//Maze data accessers
	int MazeX();
	int MazeY();
	std::vector < std::vector < bool > > MazeMap();
	std::vector < std::vector < bool > > Path();

	bool ENM();
	void ENM(bool en);

	bool EXM();
	void EXM(bool ex);

	//A* methods
	bool isAllowable(int x, int y);
	bool isDone(std::pair<int, int>, int x, int y);
	void AStar(std::pair<int,int> a, std::pair<int,int> b);
	void CheckSuccessor(std::pair<int, int> e, int x, int y);
};