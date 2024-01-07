#ifndef ISERVICECUSTOMERMEDIATOR_H
#define ISERVICECUSTOMERMEDIATOR_H

#include "Customer.h"

class IServiceCustomerMediator
{
public:
	virtual void CallCustomer(Customer& customer) = 0;
	virtual void MakingAction() = 0;
	// Add more methods as needed for communication between components
	virtual ~IServiceCustomerMediator() = default;
};

#endif
