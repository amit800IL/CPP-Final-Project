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

// Method to check if the priority queue is empty
bool STLCustomerQueue::IsEmpty() const
{
	return customerPriorityQueue.empty();
}
