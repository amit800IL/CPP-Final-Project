#include "STLCustomerQueue.h"

void STLCustomerQueue::Enqueue(unique_ptr<Customer> customer)
{
	customerPriorityQueue.push(move(customer));
}

void STLCustomerQueue::Dequeue()
{
	if (!customerPriorityQueue.empty())
	{
		cout << "Customer dequeued from the priority queue." << std::endl;
		customerPriorityQueue.pop();
	}
	else
	{
		cout << "Priority queue is empty." << std::endl;
	}
}

bool STLCustomerQueue::IsEmpty() const
{
	return customerPriorityQueue.empty();
}

priority_queue<unique_ptr<Customer>>& STLCustomerQueue::GetPriorityQueue()
{
	return customerPriorityQueue;
}

