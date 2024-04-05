#ifndef STLCUSTOMERQUEUE_H
#define STLCUSTOMERQUEUE_H

#include "Customer.h"
#include <algorithm>
#include "IServiceCustomerMediator.h"
#include "MailCustomerCommunication.h"
#include <queue>
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"
#include <functional>
#include <memory>
#include "CustomerComperator.h"

using namespace std;

struct CustomerAgeComparator
{
public:
	bool operator()(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const {
		// Compare customers based on their age
		return a->CustomerAge() > b->CustomerAge();
	}
};

#pragma once
class STLCustomerQueue
{

private:
	priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerAgeComparator> customerPriorityQueue;
public:
	void PlaceCustomerInQueue(std::unique_ptr<Customer> customer);
	void GetCustomersFromQueue(shared_ptr<IServiceCustomerMediator> mailActionsManager);
	bool IsEmpty() const;
};

#endif

