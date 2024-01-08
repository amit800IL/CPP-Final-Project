
#ifndef PROVIDERCUSTOMERCOMMUNICATION_H
#define PROVIDERCUSTOMERCOMMUNICATION_H

#include "IServiceCustomerMediator.h"

class ServiceCustomerCommunication : public IServiceCustomerMediator
{
public:
	void CallCustomer(Customer& customer, void (IServiceCustomerMediator::* MakingAction)()) override;
	void MakingAction() override;
};


#endif