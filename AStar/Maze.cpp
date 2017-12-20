// Author: Josh Davis
// Last Modified: 12/20/2017
// Purpose: Generates maze data and solves using A*

#include "Maze.h";

Maze::Maze()
{

	srand(static_cast<unsigned int>(time(NULL)));

	//simple maze generation to test A*
	//adapted from http://www.roguebasin.com/index.php?title=Simple_maze

	std::list < std::pair < int, int> > drillers;

	walls.resize(default_maze_size_y);
	for (size_t y = 0; y < default_maze_size_y; y++)
		walls[y].resize(default_maze_size_x);

	for (size_t x = 0; x < default_maze_size_x; x++)
		for (size_t y = 0; y < default_maze_size_y; y++)
			walls[y][x] = false;

	drillers.push_back(std::make_pair(default_maze_size_x / 2, default_maze_size_y / 2));
	while (drillers.size() > 0)
	{
		std::list < std::pair < int, int> >::iterator m, _m, temp;
		m = drillers.begin();
		_m = drillers.end();
		while (m != _m)
		{
			bool remove_driller = false;
			switch (rand() % 4)
			{
			case 0:
				(*m).second -= 2;
				if ((*m).second < 0 || walls[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				walls[(*m).second + 1][(*m).first] = true;
				break;
			case 1:
				(*m).second += 2;
				if ((*m).second >= default_maze_size_y || walls[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				walls[(*m).second - 1][(*m).first] = true;
				break;
			case 2:
				(*m).first -= 2;
				if ((*m).first < 0 || walls[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				walls[(*m).second][(*m).first + 1] = true;
				break;
			case 3:
				(*m).first += 2;
				if ((*m).first >= default_maze_size_x || walls[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				walls[(*m).second][(*m).first - 1] = true;
				break;
			}
			if (remove_driller)
				m = drillers.erase(m);
			else
			{
				drillers.push_back(std::make_pair((*m).first, (*m).second));

				drillers.push_back(std::make_pair((*m).first, (*m).second));

				walls[(*m).second][(*m).first] = true;
				++m;
			}
		}
	}

	//initialize nodes
	for (int i = 0; i < default_maze_size_x; i++) 
	{
		nodes.push_back(std::vector<Node*>());

		for (int j = 0; j < default_maze_size_y; j++) 
		{
			nodes[i].push_back(new Node(i, j, 0.0, 0.0));
		}
	}
}


Maze::Maze(int w, int h)
{
	//todo: add configurable maze size
}

Maze::~Maze()
{
	//delete arrays of nodes, open, and closed
	for (int i = 0; i < default_maze_size_x; i++)
	{
		for (int j = 0; j < default_maze_size_y; j++)
		{
			delete nodes[i][j];
		}
	}
	/*for (int i = 0; i < OPEN.size(); i++) 
	{
		delete OPEN[i];
	}
	for (int i = 0; i < CLOSED.size(); i++) 
	{
		delete CLOSED[i];
	}*/
}

int Maze::MazeX() 
{
	return default_maze_size_x;
}
int Maze::MazeY()
{
	return default_maze_size_y;
}

std::vector < std::vector < bool > > Maze::MazeMap()
{
	return this->walls;
}

bool Maze::ENM() { return enM; }
void Maze::ENM(bool value) { enM = value; }

bool Maze::EXM() { return exM; }
void Maze::EXM(bool value) { exM = value; }

//check if parameters are within maze size
bool Maze::isAllowable(int x, int y)
{
	if ((x >= 0) && (x < default_maze_size_x) && (y >= 0) && (y < default_maze_size_y))
	{
		if (walls[x][y] == true) 
		{
			return false;
		}
	};

	return true;
}

//check for end of A*
bool Maze::isDone(std::pair<int, int> end, int x, int y)
{
	
	if (x == end.first && y == end.second) 
	{
		return true;
	}
	return false;
}

//run through A* algorithm
void Maze::AStar(std::pair<int, int> start, std::pair<int, int> end)
{
	//check conditions that would either break the algorithm
	//or end it instantly ;)
	if ((!isAllowable(start.first, start.second) && !isAllowable(end.first, end.second)) || isDone(end, start.first, start.second))
	{
		return;
	}

	//start with initial values for i and j
	int i = start.first;
	int j = start.second;

	//initialize OPEN with the starting node
	//OPEN.push_back(nodes[i][j]);
	OPEN = nodes[i][j];

	for (int i = 0; i < default_maze_size_x; i++)
	{
		CLOSED.push_back(std::vector<bool>());

		for (int j = 0; j < default_maze_size_y; j++)
		{
			CLOSED[i].push_back(false);
		}
	}

	int k = nodes.size();

	//while list not empty
	while (k > 0) {

		//find node with least f
		Node * q = OPEN;

		//pop q off open list
		//OPEN.pop_back();
		//OPEN = nullptr;

		i = q->getX();
		j = q->getY();

		CLOSED[i][j] = true;

		/* with the original node being (i, j), successors are each direction and diagonal, i.e.
		(i - 1, j), (i + 1, j), (i, j + 1), (i, j - 1), 
		(i - 1, j + 1), (i - 1, j - 1), (i + 1, j + 1), (i + 1, j - 1)*/

		// for each successor, check and process appropriate lists
		CheckSuccessor(end, i - 1, j);
		CheckSuccessor(end, i + 1, j);
		CheckSuccessor(end, i, j + 1);
		CheckSuccessor(end, i, j - 1);
		CheckSuccessor(end, i - 1, j + 1);
		CheckSuccessor(end, i - 1, j - 1);
		CheckSuccessor(end, i + 1, j + 1);
		CheckSuccessor(end, i + 1, j - 1);


		//push q to closed list
		//CLOSED.push_back(q);

		i--;
	}
}

void Maze::CheckSuccessor(std::pair<int, int> e, int x, int y)
{
	float tempg, temph;

	if (isAllowable(x, y)) 
	{

		//if goal, stop
		if (isDone(e, x, y)) 
		{
			return;
		}
		//if node with same position as successor is in CLOSED which
		//has a lower f than successor, skip
		else if (CLOSED[x][y] == false) {
			
			tempg = nodes[x][y]->getG() + 1.0;
			temph = nodes[x][y]->hCost(x, y);

			//if node with same position as successor is in OPEN which 
			//has a lower f than successor, skip
			float temp = nodes[x][y]->getF();
			if (temp == FLT_MAX ||  temp > (tempg + temph))
			{
				OPEN = nodes[x][y];

				nodes[x][y]->setG(tempg);
				nodes[x][y]->setH(temph);
				nodes[x][y]->setF(tempg + temph);
			}

		}

	}
}