#pragma once

#include <iostream>
#include <iterator>
#include <memory>


#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"

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
	std::unique_ptr<Customer> lastServedCustomer;
	Node* tail;

public:
	CustomerQueue() : head(nullptr), tail(nullptr) {}

	bool IsEmpty() const;

	void Enqueue(Customer&& customer);

	void Dequeue();

	void EnqueueElderly(std::unique_ptr<Node> newNode);
	void EnqueueClostInLine(std::unique_ptr<Node> newNode);
};


#endif 