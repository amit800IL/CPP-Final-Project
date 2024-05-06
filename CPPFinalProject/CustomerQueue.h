#pragma once

#include <iostream>
#include <iterator>
#include <memory>
#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"
#include "MailCustomerCommunication.h"


#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

using namespace std;

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
	Node* tail;
	int customerQueueCount = 0;

public:
	CustomerQueue() : head(nullptr), tail(nullptr) {}

	bool IsEmpty() const;

	void Enqueue(const unique_ptr<Customer>& customer);

	void Dequeue(Node* current);


	bool IsRegularCustomer(Node* customerNode) const;

	bool IsElderlyCustomer(Node* customerNode) const;

	int findActionIndex(const vector<MailActions>& sequence, MailActions action) const;

	void ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager);

	int CalculateCustomerPriority(bool lastServedRegular, Node* node) const;
	void ProcessCustomer(Node* customerNode, shared_ptr<MailCustomerCommunication> mailActionsManager);

	bool IsCustomerInDataFile(int customerID) const;
};


#endif 