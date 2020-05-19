#include "ShortestPath.h"
#include "Graph.h"
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)  // allow the use of strtok in visual studio
using namespace std;

//static
vector<int> split_string_to_number(char* num_string)
{
	vector<int> res;
	string line = num_string;

	while (!line.empty())
	{
		if (line.find(" ") == string::npos) 
		{
			res.push_back(stoi(line));
			line.clear();
			break;
		}
		string s_temp = line.substr(0, line.find(" "));
		res.push_back(stoi(s_temp));
		line.erase(0, line.find(" ") + 1);
	}
	return res;
}

bool ShortestPath::init(double edge_density, int distance_range[2], int v_number)
{
	if (this->graph.generate(edge_density, distance_range, v_number))
		return true;
	else
		return false;
}

bool ShortestPath::init_from_file(string file_addr)
{
	
	ifstream fin(file_addr);								//construct an ifstream and open it
	char buff[MAX_LINE] = { 0 };
	fin.getline(buff, sizeof(buff));
	int vertices = atoi(buff);

	this->graph.init(vertices);								//init graph with infinity
	while(fin.getline(buff, sizeof(buff)))
	{
		vector<int> number = split_string_to_number(buff);
		this->graph.set_edge_value(number[0], number[1], number[2]);
		//cout << number[0] << " " << number[1] << " " << number[2] << endl;
	}
	return true;
}

bool ShortestPath::dijkstra(int begin)
{
	vector<int> results(this->graph.V());
	for (int v = 0; v < this->graph.V(); v++)			// init data
	{
		results[v] = 0;									// init the results as shortest 
		this->D.Insert(this->graph.map[begin][v]);
		this->P.Insert(-1);								//init the route path array as -1
	}

	//there is no need to calculate begining node v0 to v0
	this->D.queue[begin] = 0;							
	results[begin] = 1;

	// main loop for solving the problem，get the shortest path from v0 to v at each epoch
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

// Prim算法生成最小生成树  
double ShortestPath::MiniSpanTree_Prim(void)
{
	int j, k;
	double min;
	vector<int> adjvex(this->graph.V());		// 保存相关顶点下标 
	vector<int> lowcost(this->graph.V());		// 保存相关顶点间边的权值 
	lowcost[0] = 0;								// 初始化第一个权值为0，即v0加入生成树 
												// lowcost的值为0，在这里就是此下标的顶点已经加入生成树 
	adjvex[0] = 0;								// 初始化第一个顶点下标为0 
	double costs = 0;

	for (int i = 1; i < this->graph.V(); i++)	// 循环除下标为0外的全部顶点 
	{
		lowcost[i] = this->graph.map[0][i];		// 将v0顶点与之有边的权值存入数组 
		adjvex[i] = 0;							// 初始化都为v0的下标 
	}	
	for (int i = 1; i < this->graph.V(); i++)
	{
		min = INFINITY;							// 初始化最小权值为∞， 
												// 通常设置为不可能的大数字如32767、65535等 
		j = 1; k = 0;
		while (j < this->graph.V())				// 循环全部顶点 
		{
			if (lowcost[j] != 0 && lowcost[j] < min)// 如果权值不为0且权值小于min 
			{
				min = lowcost[j];				// 则让当前权值成为最小值 
				k = j;							// 将当前最小值的下标存入k 
			}
			j++;
		}
		cout << "the cost from edge " << left << setw(2)<< adjvex[k] << " to edge " << left << setw(2) << k << " : " << lowcost[k] << endl;
		costs += lowcost[k];
		lowcost[k] = 0;							// 将当前顶点的权值设置为0,表示此顶点已经完成任务 
		for (int j = 1; j < this->graph.V(); j++)	// 循环所有顶点 
		{
			if (lowcost[j] != 0 && this->graph.map[k][j] < lowcost[j])
			{									// 如果下标为k顶点各边权值小于此前这些顶点未被加入生成树权值 
				lowcost[j] = this->graph.map[k][j];// 将较小的权值存入lowcost相应位置 
				adjvex[j] = k;					// 将下标为k的顶点存入adjvex 
			}
		}
	}
	return costs;
}


