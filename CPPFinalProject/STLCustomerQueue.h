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


enum class MailActions;

int CompareActions(MailActions actions);

struct CustomerComparator
{
	bool operator()(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const
	{
		int priorityScoreA = a->GetPriorityScore();
		int priorityScoreB = b->GetPriorityScore();

		if (priorityScoreA != priorityScoreB) 
		{
			return priorityScoreA < priorityScoreB;
		}
		else
		{
			return a->CustomerAge() > b->CustomerAge();
		}
	}
};


class STLCustomerQueue
{

private:
	priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerComparator> regularQueue;
	priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerComparator> elderlyQueue;
public:
	void PlaceCustomerInQueue(unique_ptr<Customer> customer);
	void GetCustomersFromQueue(shared_ptr<MailCustomerCommunication> mailActionsManager);
	bool IsEmpty() const;
	const unique_ptr<Customer>& ServeNextCustomer(priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerComparator>& queue, shared_ptr<MailCustomerCommunication> mailActionsManager);
	const Customer& GetNextCustomer() const;
};




#endif

