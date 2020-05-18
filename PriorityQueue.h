#pragma once
#include "Graph.h"
#include <vector>
#include <cstdbool>

class PriorityQueue
{
	public:
		vector<double> queue;
		//changes the priority(node value) of queue element.
		bool chgPrioirity(int priority);

		//removes the top element of the queue.
		bool minPrioirty(void);

		//does the queue contain queue_element.
		bool contains(int queue_element);

		//insert queue_element into queue
		bool Insert(double queue_element);

		//returns the top element of the queue.
		int top(void);
};

