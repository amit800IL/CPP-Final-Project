#ifndef ISERVICECUSTOMERMEDIATOR_H
#define ISERVICECUSTOMERMEDIATOR_H

#include "Customer.h"
#include "MailOfficial.h"

enum class MailActions;

class IServiceCustomerMediator
{
public:
	virtual void CallCustomer(Customer& customer) = 0;
	virtual MailActions MakingAction() = 0;
	virtual ~IServiceCustomerMediator() = default;
};

#endif
