#ifndef STLCUSTOMERQUEUE_H
#define STLCUSTOMERQUEUE_H

#include "Customer.h"
#include <algorithm>
#include <queue>

using namespace std;

#pragma once
class STLCustomerQueue
{
private:
	priority_queue<unique_ptr<Customer>> customerPriorityQueue;
public:
	void Enqueue(std::unique_ptr<Customer> customer);
	void Dequeue();
	bool IsEmpty() const;
	priority_queue<unique_ptr<Customer>>& GetPriorityQueue();

};

#endif

