
#ifndef ELDERLYCUSTOMER_H
#define ELDERLYCUSTOMER_H

#include "Customer.h"

class MailClerk;

class ElderlyCustomer: public Customer
{
public:
	ElderlyCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction);

	ElderlyCustomer(ElderlyCustomer&& customer) noexcept;

	~ElderlyCustomer() override = default;
};

#endif