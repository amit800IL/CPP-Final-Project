
#ifndef ELDERLYCUSTOMER_H
#define ELDERLYCUSTOMER_H

#include "Customer.h"

class MailClerk;

class ElderlyCustomer: public Customer
{
public:
	ElderlyCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk);

	ElderlyCustomer(ElderlyCustomer&& customer) noexcept;

	~ElderlyCustomer() override = default;
};

#endif