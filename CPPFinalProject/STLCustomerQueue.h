#ifndef STLCUSTOMERQUEUE_H
#define STLCUSTOMERQUEUE_H

#include "Customer.h"
#include <queue>
#include <algorithm>

using namespace std;

#pragma once
class STLCustomerQueue
{
private:
public:
	queue<unique_ptr<Customer>> customerPriorityQueue;
	void Enqueue(std::unique_ptr<Customer> customer);
	void Dequeue();
	bool IsEmpty() const;
};

#endif

