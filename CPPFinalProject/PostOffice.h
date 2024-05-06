#pragma once

#ifndef POSTOFFICE_H

#define POSTOFFICE_H

#include "Customer.h";
#include "CustomerQueue.h"
#include "MailClerk.h"
#include "MailCustomerCommunication.h"
#include "STLCustomerQueue.h"

class PostOffice
{
public:
	PostOffice();
private:
	void PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
	void UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
	void BaseSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);
	void CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);
};


#endif