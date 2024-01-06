#pragma once

#include "Customer.h"
#include <iostream>
#include <memory>

#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

struct Node
{
	Customer& customer;
	std::unique_ptr<Node> next;

	Node(Customer& customer) : customer(customer), next(nullptr) {}
};

class CustomerQueue
{
private:
	std::unique_ptr<Node> head;
	Node* tail;

public:
	CustomerQueue() : head(nullptr), tail(nullptr) {}

	bool IsEmpty() const;

	void Enqueue(Customer&& customer);

	void Dequeue();
};


#endif 