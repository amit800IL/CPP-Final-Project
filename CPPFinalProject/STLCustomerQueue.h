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
		shared_ptr<MailClerk> clerkA = a->GetAssignedClerk();
		shared_ptr<MailClerk> clerkB = b->GetAssignedClerk();

		const vector<MailActions>& actionSequenceA = clerkA->GetActionSequence();
		const vector<MailActions>& actionSequenceB = clerkB->GetActionSequence();

		auto findActionIndex = [&](const vector<MailActions>& sequence, MailActions action)
			{
				auto it = find(sequence.begin(), sequence.end(), action);
				if (it != sequence.end()) {
					return distance(sequence.begin(), it);
				}
			};

		MailActions chosenActionA = a->GetCustomerAction();
		MailActions chosenActionB = b->GetCustomerAction();

		int indexA = findActionIndex(actionSequenceA, chosenActionA);
		int indexB = findActionIndex(actionSequenceB, chosenActionB);

		if (indexA != -1 && indexB != -1) {
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

