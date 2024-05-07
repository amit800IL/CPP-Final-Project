#ifndef REGUALRCUSTOMER_H
#define REGUALRCUSTOMER_H

#include "Customer.h"

class MailClerk;

class RegularCustomer: public Customer
{
public:
	RegularCustomer(string name, const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk);

	RegularCustomer(RegularCustomer&& customer) noexcept;

	~RegularCustomer() override = default;
};

#endif 
