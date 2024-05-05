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

		// Get assigned clerks for both customers
		shared_ptr<MailClerk> clerkA = a->GetAssignedClerk();
		shared_ptr<MailClerk> clerkB = b->GetAssignedClerk();

		if (clerkA && clerkB)
		{
			const vector<MailActions>& actionSequenceA = clerkA->GetActionSequence();
			const vector<MailActions>& actionSequenceB = clerkB->GetActionSequence();

			int indexA = findActionIndex(actionSequenceA, a->GetCustomerAction());
			int indexB = findActionIndex(actionSequenceB, b->GetCustomerAction());

			if (indexA != -1 && indexB != -1)
			{
				return indexA > indexB;
			}
		}

		return a->CustomerAge() > b->CustomerAge();
		// Check if the last served customer was regular
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

