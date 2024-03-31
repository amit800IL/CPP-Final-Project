
#ifndef MAILCUSTOMERCOMMUNICATION_H
#define MAILCUSTOMERCOMMUNICATION_H

#include <iostream>
#include <memory>
#include "MailActions.h"
#include "Customer.h"
#include "IServiceCustomerMediator.h"
#include "MailOfficial.h"

using namespace std;

class MailCustomerCommunication : public IServiceCustomerMediator
{

private:
	unique_ptr<MailOfficial> mailOfficial;
public:
	void CallCustomer(Customer& customer) override;
	MailActions MakingAction() override;
};


#endif