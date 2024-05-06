#ifndef STLCUSTOMERQUEUE_H
#define STLCUSTOMERQUEUE_H

#include "Customer.h"
#include "CustomerComperator.h"
#include "ElderlyCustomer.h"
#include "MailCustomerCommunication.h"
#include "RegularCustomer.h"
#include <memory>
#include <queue>

using namespace std;
#pragma once

class STLCustomerQueue
{

public:

	void Enqueue(unique_ptr<Customer> customer);
	void ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager);

private:

	vector<unique_ptr<Customer>> customerQueue;
	bool IsEmpty() const;
	void Dequeue(int index);
	int FindHighestPriorityCustomerIndex(bool lastServedRegular) const;
	int CalculateCustomerPriority(bool lastServedRegular, const unique_ptr<Customer>& customer) const;
	void ProcessCustomer(const unique_ptr<Customer>& customer, shared_ptr<MailCustomerCommunication> mailActionsManager);
	bool IsCustomerInDataFile(int customerID) const;
	bool IsRegularCustomer(const unique_ptr<Customer>& customer) const;
	bool IsElderlyCustomer(const unique_ptr<Customer>& customer) const;
};



#endif

