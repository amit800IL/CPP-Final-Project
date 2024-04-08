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
#include "CustomerComperator.h"

using namespace std;
//
//struct CustomerAgeComparator {
//    bool operator()(const std::unique_ptr<Customer>& a, const std::unique_ptr<Customer>& b) const {
//        // Determine priority based on customer type and age
//        bool aIsElderly = (a->CustomerAge() > 65);
//        bool bIsElderly = (b->CustomerAge() > 65);
//
//        if (aIsElderly && !bIsElderly) {
//            return true; // a (elderly) has higher priority than b (regular)
//        }
//        else {
//            // Same customer type, compare by age
//            return a->CustomerAge() >= b->CustomerAge(); // Older customers have higher priority
//        }
//    }
//};
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

