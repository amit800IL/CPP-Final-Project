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
	int findActionIndex(const vector<MailActions>& sequence, MailActions action) const
	{
		vector<MailActions>::const_iterator it = find(sequence.begin(), sequence.end(), action);
		if (it != sequence.end()) {
			return distance(sequence.begin(), it);
		}
		return -1;
	}

	bool operator()(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const
	{
		shared_ptr<MailClerk> clerkA = a->GetAssignedClerk();
		shared_ptr<MailClerk> clerkB = b->GetAssignedClerk();

		const vector<MailActions>& actionSequenceA = clerkA->GetActionSequence();
		const vector<MailActions>& actionSequenceB = clerkB->GetActionSequence();

		int indexA = findActionIndex(actionSequenceA, a->GetCustomerAction());
		int indexB = findActionIndex(actionSequenceB, b->GetCustomerAction());

		if (indexA != -1 && indexB != -1)
		{
			return indexA > indexB;
		}

		return a->CustomerAge() > b->CustomerAge();
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

