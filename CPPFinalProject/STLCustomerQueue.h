#ifndef STLCUSTOMERQUEUE_H
#define STLCUSTOMERQUEUE_H

#include "Customer.h"
#include "CustomerComperator.h"
#include "ElderlyCustomer.h"
#include "IServiceCustomerMediator.h"
#include "MailCustomerCommunication.h"
#include "RegularCustomer.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <queue>

using namespace std;
#pragma once

struct CustomerComparator 
{
	bool operator()(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const
	{

		bool aIsElderly = dynamic_cast<RegularCustomer*>(a.get()) != nullptr;
		bool bIsElderly = dynamic_cast<ElderlyCustomer*>(b.get()) != nullptr;

		return a->GetCustomerNumber() > b->GetCustomerNumber(); // If both are same type, use customer number as tiebreaker
	}
};

class STLCustomerQueue
{

private:
	std::priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerComparator> customerPriorityQueue;
public:
	void PlaceCustomerInQueue(std::unique_ptr<Customer> customer);
	void GetCustomersFromQueue(shared_ptr<IServiceCustomerMediator> mailActionsManager);
	bool IsEmpty() const;
};
1
#endif

