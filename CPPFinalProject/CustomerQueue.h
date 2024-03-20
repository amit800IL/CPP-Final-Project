#pragma once

#include <iostream>
#include <iterator>
#include <memory>
#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"


#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

using namespace std;


struct Node
{
	Customer& customer;
	unique_ptr<Node> next;

	Node(Customer& customer) : customer(customer), next(nullptr) {}
};

class CustomerQueue
{
private:
	unique_ptr<Node> head;
	unique_ptr<Customer> lastServedCustomer;
	unique_ptr<Node> tail;

public:
	CustomerQueue() : head(nullptr), tail(nullptr) {}

	bool IsEmpty() const;

	void Enqueue(Customer&& customer);

	const Node& GetHead() const;

	unique_ptr<Node> Dequeue();
};


#endif 