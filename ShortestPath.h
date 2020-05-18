#pragma once
#include "Graph.h"
#include "PriorityQueue.h"
class ShortestPath
{
	public:
		Graph graph;
		PriorityQueue D;
		PriorityQueue P;
		bool init(double edge_density, int distance_range[2]);
		bool dijkstra(int begin);
		void print_results(void);
		double calculate_mean_length(void);
};