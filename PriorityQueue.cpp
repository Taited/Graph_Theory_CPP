#include "PriorityQueue.h"
//changes the priority(node value) of queue element.
bool PriorityQueue::chgPrioirity(int priority)
{
	return true;
}

//removes the top element of the queue.
bool PriorityQueue::minPrioirty(void)
{
	return true;
}

//does the queue contain queue_element.
bool PriorityQueue::contains(int queue_element)
{
	return true;
}

//insert queue_element into queue
bool PriorityQueue::Insert(double queue_element)
{
	if (this->queue.size() > MAX_VERTICES)
	{
		return false;
	}
	this->queue.push_back(queue_element);
	return true;
}

//returns the top element of the queue.
int top(void)
{
	return 1;
}