#include "Graph.h"


inline int Graph::V(void)
{
	return this->vertices;
}

inline int Graph::E(void)
{
	int counter = 0;
	for (int i = 0; i < this->V(); i++)
	{
		for (int j = i; j < this->V(); j++)
		{
			if (i != j && this->map[i][j]!=INFINITY)
			{
				counter += 1;
			}
		}
	}
	return counter;
}

//set the distances of all of the edges as infinity
bool Graph::init(int v_number = MAX_VERTICES)
{
	this->vertices = v_number;
	for (int i = 0; i < this->vertices; i++)
	{
		for (int j = i; j < this->vertices; j++)
		{
			if (i == j)
			{
				this->set_edge_value(i, j, 0);
			}
			else
			{
				this->set_edge_value(i, j, INFINITY);
			}
		}
	}
	return true;
}

bool Graph::generate(double edge_density, int distance_range[2], int v_number)
{
	if (!this->init(v_number))  //initiate firstly
	{
		return false;
	}
	for (int i = 0; i < this->V(); i++)
	{
		for (int j = i; j < this->V(); j++)
		{
			if (i != j)
			{
				double flag = rand() * 1.0 / RAND_MAX;  //randomly generate a number with the range of 0~1
				if (flag <= edge_density)
				{
					double distance;
					distance = rand() % (distance_range[1] - distance_range[0]) + (double) distance_range[0];
					this->set_edge_value(i, j, distance);
				}
			}
		}
	}
	return true;
}

//print out the connectivity matrices
void Graph::show_graph(void)
{
	for (int i = 0; i < this->vertices; i++)
	{
		for (int j = 0; j < this->vertices; j++)
		{
			cout << left << setw(3) << this->map[i][j] << ' ';
		}
		cout << endl << endl;
	}
}

//tests whether there is an edge from node x to node y.
bool Graph::adjacent(int x, int y)
{
	if (this->map[x][y] != INFINITY)
		return true;
	else
		return false;
}

//lists all nodes y such that there is an edge from x to y.
vector<int> Graph::neighbors(int x)
{
	vector<int> results;
	for (int i = 0; i < this->vertices; i++)
	{
		if (this->adjacent(x, i))
		{
			results.push_back(i);
		}
	}
	return results;
}


//removes the edge from x to y, if it is there.
bool Graph::deletes(int x, int y)
{
	this->map[x][y] = INFINITY;
	return true;
}


//returns the value associated to the edge(x, y).
double Graph::get_edge_value(int x, int y)
{
	return this->map[x][y];
}

//sets the value associated to the edge(x, y) to v.
inline void Graph::set_edge_value(int x, int y, double v)
{
	this->map[x][y] = v;
	this->map[y][x] = v;
}