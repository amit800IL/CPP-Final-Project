#pragma once

#include <iostream>
#include <iterator>
#include <memory>
#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"
#include "MailCustomerCommunication.h"
#include "CustomerQueueIterator.h"


#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

using namespace std;

class CustomerQueueIterator;

struct Node
{
	const unique_ptr<Customer>& customer;
	int priority;
	unique_ptr<Node> next;

	Node(const unique_ptr<Customer>& customer, int priority) : customer(customer), priority(priority), next(nullptr) {}
};

class CustomerQueue
{
private:
	unique_ptr<Node> head;
	unique_ptr<Customer> lastServedCustomer;
	Node* tail;

public:
	CustomerQueue() : head(nullptr), tail(nullptr) {}

	bool IsEmpty() const;

	void Enqueue(const unique_ptr<Customer>& customer);

	unique_ptr<Node> Dequeue();

	void ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager);

	CustomerQueueIterator begin() const;
	CustomerQueueIterator end() const;
};


#endif 