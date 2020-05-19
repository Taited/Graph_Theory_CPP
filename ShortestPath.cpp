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

	// main loop for solving the problem��get the shortest path from v0 to v at each epoch
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

// Prim�㷨������С������  
double ShortestPath::MiniSpanTree_Prim(void)
{
	int j, k;
	double min;
	vector<int> adjvex(this->graph.V());		// ������ض����±� 
	vector<int> lowcost(this->graph.V());		// ������ض����ߵ�Ȩֵ 
	lowcost[0] = 0;								// ��ʼ����һ��ȨֵΪ0����v0���������� 
												// lowcost��ֵΪ0����������Ǵ��±�Ķ����Ѿ����������� 
	adjvex[0] = 0;								// ��ʼ����һ�������±�Ϊ0 
	double costs = 0;

	for (int i = 1; i < this->graph.V(); i++)	// ѭ�����±�Ϊ0���ȫ������ 
	{
		lowcost[i] = this->graph.map[0][i];		// ��v0������֮�бߵ�Ȩֵ�������� 
		adjvex[i] = 0;							// ��ʼ����Ϊv0���±� 
	}	
	for (int i = 1; i < this->graph.V(); i++)
	{
		min = INFINITY;							// ��ʼ����СȨֵΪ�ޣ� 
												// ͨ������Ϊ�����ܵĴ�������32767��65535�� 
		j = 1; k = 0;
		while (j < this->graph.V())				// ѭ��ȫ������ 
		{
			if (lowcost[j] != 0 && lowcost[j] < min)// ���Ȩֵ��Ϊ0��ȨֵС��min 
			{
				min = lowcost[j];				// ���õ�ǰȨֵ��Ϊ��Сֵ 
				k = j;							// ����ǰ��Сֵ���±����k 
			}
			j++;
		}
		cout << "the cost from edge " << left << setw(2)<< adjvex[k] << " to edge " << left << setw(2) << k << " : " << lowcost[k] << endl;
		costs += lowcost[k];
		lowcost[k] = 0;							// ����ǰ�����Ȩֵ����Ϊ0,��ʾ�˶����Ѿ�������� 
		for (int j = 1; j < this->graph.V(); j++)	// ѭ�����ж��� 
		{
			if (lowcost[j] != 0 && this->graph.map[k][j] < lowcost[j])
			{									// ����±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ 
				lowcost[j] = this->graph.map[k][j];// ����С��Ȩֵ����lowcost��Ӧλ�� 
				adjvex[j] = k;					// ���±�Ϊk�Ķ������adjvex 
			}
		}
	}
	return costs;
}


