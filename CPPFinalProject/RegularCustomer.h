#ifndef REGUALRCUSTOMER_H
#define REGUALRCUSTOMER_H

#include "Customer.h"

class MailClerk;

class RegularCustomer: public Customer
{
public:
	RegularCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction);

	RegularCustomer(RegularCustomer&& customer) noexcept;

	~RegularCustomer() override = default;
};

#endif 
