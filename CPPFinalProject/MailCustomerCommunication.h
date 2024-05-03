
#ifndef MAILCUSTOMERCOMMUNICATION_H
#define MAILCUSTOMERCOMMUNICATION_H

#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>
#include "Customer.h"
#include "MailClerk.h"
#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"

using namespace std;

enum class MailActions;
class MailClerk;

class MailCustomerCommunication
{

private:
	vector<shared_ptr<MailClerk>> clerks;
public:
	MailCustomerCommunication(const vector<shared_ptr<MailClerk>>& clerks);
	shared_ptr<MailClerk> FindAvailableClerk(const MailActions& action) const;
	unique_ptr<Customer> CreateCustomer();
	void CallCustomer(const Customer& customer);
	MailActions ChooseAction();

	~MailCustomerCommunication() = default;
};


#endif