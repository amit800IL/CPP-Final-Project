
#ifndef MAILCUSTOMERCOMMUNICATION_H
#define MAILCUSTOMERCOMMUNICATION_H

#include <iostream>
#include <memory>
#include "MailActions.h"
#include "Customer.h"
#include "IServiceCustomerMediator.h"
#include "MailClerk.h"

using namespace std;

class MailCustomerCommunication : public IServiceCustomerMediator
{

private:
	std::vector<std::shared_ptr<MailClerk>> clerks;
public:
	MailCustomerCommunication(const std::vector<std::shared_ptr<MailClerk>>& clerks);
	MailActions GetAvailableAction(const MailClerk& clerk) const;
	void CallCustomer(Customer& customer) override;
	MailActions MakingAction(const MailClerk& clerk) const;
	MailActions MakingAction() override;
};


#endif