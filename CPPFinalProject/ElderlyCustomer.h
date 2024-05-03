
#ifndef ELDERLYCUSTOMER_H
#define ELDERLYCUSTOMER_H

#include "Customer.h"


class ElderlyCustomer: public Customer
{
public:
	ElderlyCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction);

	ElderlyCustomer(ElderlyCustomer&& customer) noexcept;

	int GenerateCustomerNumber() override;

	~ElderlyCustomer() override = default;
};

#endif