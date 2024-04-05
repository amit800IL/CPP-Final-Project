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

