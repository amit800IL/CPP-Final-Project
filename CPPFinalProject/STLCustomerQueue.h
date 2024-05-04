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

int CompareActions(MailActions actions);

struct CustomerComparator
{
    bool operator()(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const
    {
        bool aIsElderly = dynamic_cast<ElderlyCustomer*>(a.get()) != nullptr;
        bool bIsElderly = dynamic_cast<ElderlyCustomer*>(b.get()) != nullptr;

        // Get the action priorities for each customer
        int aActionPriority = CompareActions(a->GetCustomerAction());
        int bActionPriority = CompareActions(b->GetCustomerAction());

        if (aActionPriority == bActionPriority) 
        {
            return a->CustomerAge() > b->CustomerAge();
        }
        else
        {
            return aActionPriority > bActionPriority;
        }
    }
};
 
class STLCustomerQueue
{

private:
	priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerComparator> customerQueue;
public:
	void PlaceCustomerInQueue(unique_ptr<Customer> customer);
	void GetCustomersFromQueue(shared_ptr<MailCustomerCommunication> mailActionsManager);
	bool IsEmpty() const;
	void ServeNextCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager);
	const Customer& GetNextCustomer() const;
};



#endif

