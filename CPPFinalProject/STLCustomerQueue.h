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
class STLCustomerQueue
{

private:
	priority_queue<unique_ptr<Customer>> customerPriorityQueue;
public:
	void PlaceCustomerInQueue(std::unique_ptr<Customer> customer);
	void GetCustomersFromQueue(shared_ptr<IServiceCustomerMediator> mailActionsManager);
	bool IsEmpty() const;
};

#endif

