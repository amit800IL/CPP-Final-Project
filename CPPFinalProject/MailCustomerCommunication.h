
#ifndef MAILCUSTOMERCOMMUNICATION_H
#define MAILCUSTOMERCOMMUNICATION_H

#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>
#include "Customer.h"
#include "MailClerk.h"

using namespace std;

enum class MailActions;
class MailClerk;

class MailCustomerCommunication
{

private:
	vector<shared_ptr<MailClerk>> clerks;
public:
	MailCustomerCommunication(const vector<shared_ptr<MailClerk>>& clerks);
	MailActions GetAvailableAction(const shared_ptr<MailClerk>& clerk) const;
	shared_ptr<MailClerk> FindAvailableClerk(const MailActions& action) const;
	void CallCustomer(const Customer& customer);
	MailActions MakingAction() const;

	~MailCustomerCommunication() = default;
};


#endif