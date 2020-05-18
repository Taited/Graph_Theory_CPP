#include "ShortestPath.h"
#include "Graph.h"

bool ShortestPath::init(double edge_density, int distance_range[2])
{
	if (this->graph.generate(edge_density, distance_range))
		return true;
	else
		return false;
}
bool ShortestPath::dijkstra(int begin)
{
	vector<int> results(MAX_VERTICES);
	for (int v = 0; v < this->graph.V(); v++)			// init data
	{
		results[v] = 0;									// init the results as shortest 
		this->D.Insert(this->graph.map[begin][v]);
		this->P.Insert(-1);								//init the route path array as -1
	}

	//there is no need to calculate begining node v0 to v0
	this->D.queue[begin] = 0;							
	results[begin] = 1;

	// main loop for solving the problem£¬get the shortest path from v0 to v at each epoch
	int flag = 0;
	double min;
	for (int v = 1; v < this->graph.V(); v++)
	{
		min = INFINITY;
		for (int w = 0; w < this->graph.V(); w++)
		{
			if (!results[w] && this->D.queue [w] < min)
			{
				flag = w;
				min = this->D.queue [w];
			}
		}
		results[flag] = 1;
		for (int w = 0; w < this->graph.V(); w++) 
		{
			// this shows we have found a shorter path
			if (!results[w] && (min + graph.map[flag][w] < this->D.queue [w]))
			{
				this->D.queue[w] = min + graph.map[flag][w];  // update current length
				this->P.queue[w] = flag;
			}
		}
	}
	return true;
}

void ShortestPath::print_results(void)
{
	int v0 = 0;
	int j;
	cout << "The reversed shortest path as below:" <<endl;
	for (int i = 1; i < this->graph.V(); ++i)
	{
		cout << "v" << v0 << " - v" << i << " : ";
		
		j = i;
		while (this->P.queue[j] != -1)
		{
			cout << this->P.queue[j] << " ";
			j = this->P.queue[j];
		}
		cout << endl;
	}
	printf("\nThe shortest distance between V0 to each other nodes:\n");
	for (int i = 1; i < this->graph.V(); ++i)
		cout << "v" << v0 << " - v" << i << " : " << this->D.queue[i] << endl;
}

double ShortestPath::calculate_mean_length(void)
{
	double sum = 0;
	double counter = 0;
	for (int i = 0; i < this->D.queue.size(); i++)
	{
		if (this->D.queue[i] != INFINITY)
		{
			sum += this->D.queue[i];
			counter += 1;
		}
	}
	return sum/counter;
}