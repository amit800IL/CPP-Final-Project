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
	unique_ptr<Node> next;

	Node(const unique_ptr<Customer>& customer) : customer(customer), next(nullptr) {}
};

class CustomerQueue
{
private:
	unique_ptr<Node> head;
	unique_ptr<Customer> lastServedCustomer;
	Node* tail;
	int customerQueueCount = 0;

public:
	CustomerQueue() : head(nullptr), tail(nullptr) {}

	bool IsEmpty() const;

	void Enqueue(const unique_ptr<Customer>& customer);

	unique_ptr<Node> Dequeue();

	void ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager);

	CustomerQueueIterator begin() const;
	CustomerQueueIterator end() const;
	void GetCustomerToServe(Node* current, shared_ptr<MailCustomerCommunication> mailActionsManager);
};


#endif 