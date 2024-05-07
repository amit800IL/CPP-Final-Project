#pragma once

#ifndef POSTOFFICE_H

#define POSTOFFICE_H

#include "Customer.h";
#include "CustomCustomerQueue.h"
#include "MailClerk.h"
#include "MailCustomerCommunication.h"
#include "STLCustomerQueue.h"

using namespace std;

class PostOffice
{
public:
	PostOffice();
	~PostOffice() = default;
private:
	void PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
	void UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
	void StlQueue(shared_ptr<MailCustomerCommunication> mailActionsManager);
	void CustomQueue(shared_ptr<MailCustomerCommunication> mailActionsManager);

};


#endif