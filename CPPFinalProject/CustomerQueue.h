#pragma once

#include <iostream>
#include <iterator>
#include <memory>
#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"


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
	std::unique_ptr<Customer> lastServedCustomer;
	Node* tail;

public:
	CustomerQueue() : head(nullptr), tail(nullptr) {}

	bool IsEmpty() const;

	void Enqueue(Customer&& customer);

	const Node& GetHead() const;

	void Dequeue();
};


#endif 