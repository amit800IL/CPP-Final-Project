
#ifndef ELDERLYCUSTOMER_H
#define ELDERLYCUSTOMER_H

#include "Customer.h"


class ElderlyCustomer: public Customer
{
public:
	ElderlyCustomer(const DateOfBirth& dateOfBirth);

	ElderlyCustomer(ElderlyCustomer&& customer) noexcept;

	int CustomerAge() const override;

	~ElderlyCustomer() override = default;
};

#endif