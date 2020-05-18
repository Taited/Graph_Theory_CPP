#include <iostream>
#include"Graph.h"
#include"ShortestPath.h"
#include"PriorityQueue.h"
using namespace std;

const int SAMPLE_TIME = 100;

int main(void)
{
	double edge_density;
	double mean_distance;
	ShortestPath find_path;
	int range[2] = { 1,10 };  // the range of each edge distance


	//SIMULATION_1
	edge_density = 0.2;
	mean_distance = 0.0;
	for (int i = 0; i < SAMPLE_TIME; i++)
	{
		find_path.init(edge_density, range);
		find_path.dijkstra(0);  // select node v0 as begining
		mean_distance += find_path.calculate_mean_length();
	}
	cout << "There average path length with density of " << edge_density << " is: " << mean_distance / SAMPLE_TIME << endl;

	//SIMULATION_2
	edge_density = 0.4;
	mean_distance = 0.0;
	for (int i = 0; i < SAMPLE_TIME; i++)
	{
		find_path.init(edge_density, range);
		find_path.dijkstra(0);  // select node v0 as begining
		mean_distance += find_path.calculate_mean_length();
	}
	cout << "There average path length with density of " << edge_density << " is: " << mean_distance / SAMPLE_TIME << endl;
	system("pause");
	return 0;
}