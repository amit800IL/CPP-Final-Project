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


struct CustomerComparator
{
    int findActionIndex(const std::vector<MailActions>& sequence, MailActions action) const
    {
        auto it = std::find(sequence.begin(), sequence.end(), action);
        return (it != sequence.end()) ? std::distance(sequence.begin(), it) : -1;
    }

    bool IsElderlyCustomer(const std::unique_ptr<Customer>& customer) const
    {
        return dynamic_cast<ElderlyCustomer*>(customer.get()) != nullptr;
    }

    bool IsRegularCustomer(const std::unique_ptr<Customer>& customer) const
    {
        return dynamic_cast<RegularCustomer*>(customer.get()) != nullptr;
    }

    int CalculateCustomerPriority(const std::unique_ptr<Customer>& customer) const
    {
        bool lastServedRegular = IsRegularCustomer(customer);

        int priority = INT_MIN;

        if (lastServedRegular && IsElderlyCustomer(customer))
        {
            priority += 100; // Additional priority for regular customers
        }

        if (customer->GetAssignedClerk())
        {
            const std::vector<MailActions>& actionSequence = customer->GetAssignedClerk()->GetActionSequence();
            int index = findActionIndex(actionSequence, customer->GetCustomerAction());
            if (index != -1)
            {
                priority = actionSequence.size() - index;
            }
        }

        return priority;
    }

    bool operator()(const std::unique_ptr<Customer>& a, const std::unique_ptr<Customer>& b) const
    {
        int priorityA = CalculateCustomerPriority(a);
        int priorityB = CalculateCustomerPriority(b);

        return priorityA < priorityB;
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

