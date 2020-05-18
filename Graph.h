#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<stdlib.h>
#include<cstdbool>
using namespace std;

const int MAX_VERTICES = 50;
// suppose there are n nodes, there will be n*(n-1)/2 edges at the most.
const int MAX_EDGES = MAX_VERTICES * (MAX_VERTICES - 1) / 2;  

class Graph
{
	public:
		int vertices = MAX_VERTICES;  //node number
		int vexs[MAX_VERTICES];  //node name
		int edges = MAX_EDGES;
		double map[MAX_VERTICES][MAX_VERTICES];


		//initialize the class
		bool init(void);

		//set values to edges with parameter of density and distance range
		bool generate(double edge_density, int distance_range[2]);

		//return the number of vertices
		int V(void);

		//return the number of edges
		int E(void);

		//tests whether there is an edge from node x to node y.
		bool adjacent(int x, int y);

		//lists all nodes y such that there is an edge from x to y.
		vector<int> neighbors(int x);
		
		//removes the edge from x to y, if it is there.
		bool deletes(int x,int y);
		
		//returns the value associated to the edge(x, y).
		double get_edge_value(int x, int y);

		//sets the value associated to the edge(x, y) to v.
		void set_edge_value(int x, int y, double v);

		//print the graph with a 2d matrix
		void show_graph(void);

};