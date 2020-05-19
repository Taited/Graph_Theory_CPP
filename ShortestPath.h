#pragma once
#include "Graph.h"
#include "PriorityQueue.h"
#include<fstream>

const int MAX_LINE = 100;
class ShortestPath
{
	public:
		Graph graph;
		PriorityQueue D;
		PriorityQueue P;
		bool init(double edge_density, int distance_range[2], int v_number);
		bool init_from_file(string file_addr);
		bool dijkstra(int begin);
		void print_results(void);
		double calculate_mean_length(void);
		//Prim
		double MiniSpanTree_Prim(void);


};