
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
public:
	MailCustomerCommunication(const std::vector<std::shared_ptr<MailClerk>>& clerks);
	MailActions GetAvailableAction(const MailClerk& clerk) const;
	std::shared_ptr<MailClerk> FindAvailableClerk(MailActions& action) const;
	void CallCustomer(Customer& customer);
	MailActions MakingAction() const;
};


#endif