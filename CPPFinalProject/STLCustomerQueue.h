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

	int findActionIndex(const vector<MailActions>& sequence, MailActions action) const
	{
		auto it = find(sequence.begin(), sequence.end(), action);
		return (it != sequence.end()) ? distance(sequence.begin(), it) : -1;
	}

	bool CustomerPriorityCompare(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const
	{
        if (!a || !b) {
            return false; // Treat nullptr as lower priority
        }

        // Get the assigned clerks for both customers
        std::shared_ptr<MailClerk> clerkA = a->GetAssignedClerk();
        std::shared_ptr<MailClerk> clerkB = b->GetAssignedClerk();

        if (!clerkA || !clerkB) {
            return false; // If clerk is missing, prioritize based on customer age
        }

        // Prioritize elderly customers over regular customers if the last served customer was regular
        bool lastServedRegular = false; // Assuming this function exists
        bool isElderlyA = dynamic_cast<ElderlyCustomer*>(a.get()) != nullptr;
        bool isElderlyB = dynamic_cast<ElderlyCustomer*>(b.get()) != nullptr;
        bool isRegularA = dynamic_cast<RegularCustomer*>(a.get()) != nullptr;
        bool isRegularB = dynamic_cast<RegularCustomer*>(b.get()) != nullptr;

        if (isRegularA && isElderlyB)
        {
            lastServedRegular = false;
            return true; // Prioritize elderly customer over regular customer
        }
        else if (lastServedRegular || (isRegularB && isElderlyA)) 
        {
            lastServedRegular = true;
            return false; // Prioritize elderly customer over regular customer
        }

        // Get the action sequences for the assigned clerks
        const std::vector<MailActions>& actionSequenceA = clerkA->GetActionSequence();
        const std::vector<MailActions>& actionSequenceB = clerkB->GetActionSequence();

        // Get the current action being performed by the customers
        MailActions actionA = a->GetCustomerAction();
        MailActions actionB = b->GetCustomerAction();

        // Find the index of the current action in the action sequence for each customer
        int indexA = findActionIndex(actionSequenceA, actionA);
        int indexB = findActionIndex(actionSequenceB, actionB);

        // Determine the priority based on the clerk's action sequence indices
        if (indexA != -1 && indexB != -1) {
            // Compare the indices of the current actions
            if (indexA != indexB) {
                return indexA > indexB; // Higher index (later action) has lower priority
            }
        }

        // Default to age priority if all other factors are equivalent
        return isElderlyA && !isRegularB; // Prioritize elderly over regular by default
	}

	bool operator()(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const
	{
		return CustomerPriorityCompare(a, b);
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

