
#ifndef MAILCUSTOMERCOMMUNICATION_H
#define MAILCUSTOMERCOMMUNICATION_H

#include <iostream>
#include <memory>
#include "Customer.h"
#include "MailClerk.h"
#include <unordered_map>

using namespace std;

enum class MailActions;
class MailClerk;

class MailCustomerCommunication
{

private:
	std::vector<std::shared_ptr<MailClerk>> clerks;
	//std::unordered_map<std::shared_ptr<MailClerk>, std::shared_ptr<Customer>> clerkCustomerMap;
public:
	MailCustomerCommunication(const std::vector<std::shared_ptr<MailClerk>>& clerks);
	MailActions GetAvailableAction(const MailClerk& clerk) const;
	void CallCustomer(Customer& customer);
	MailActions MakingAction(const MailClerk& clerk) const;
};


#endif