#ifndef REGUALRCUSTOMER_H
#define REGUALRCUSTOMER_H

#include "Customer.h"

class RegularCustomer: public Customer
{
public:
	RegularCustomer(const DateOfBirth& dateOfBirth);

	RegularCustomer(RegularCustomer&& customer) noexcept;

};

#endif 
