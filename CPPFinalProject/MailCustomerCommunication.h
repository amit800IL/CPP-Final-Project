
#ifndef MAILCUSTOMERCOMMUNICATION_H
#define MAILCUSTOMERCOMMUNICATION_H

#include "IServiceCustomerMediator.h"

class MailCustomerCommunication : public IServiceCustomerMediator
{
public:
	void CallCustomer(Customer& customer, void (IServiceCustomerMediator::* MakingAction)()) override;
	void MakingAction() override;
};


#endif