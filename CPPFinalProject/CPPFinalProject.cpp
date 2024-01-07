// CPPFinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Customer.h";
#include "CustomerQueue.h"
#include "MailActions.h"
#include <iostream>
#include "MailOfficial.h"
#include "IServiceCustomerMediator.h"
#include "ServiceCustomerCommunication.h"

int main()
{
	std::unique_ptr<IServiceCustomerMediator> mailActionsManager = std::make_unique<ServiceCustomerCommunication>();

	std::unique_ptr<MailOfficial> mailOfficial = std::make_unique<MailOfficial>(std::move(mailActionsManager));

	std::unique_ptr<CustomerQueue> customerQueue = std::make_unique<CustomerQueue>();

	std::unique_ptr<DateOfBirth> birthDate = std::make_unique<DateOfBirth>(11,12,1998);
	std::unique_ptr<DateOfBirth> birthDate2 = std::make_unique<DateOfBirth>(17,3,1955);

	std::unique_ptr<Customer> customer = std::make_unique<Customer>(true, std::move(*birthDate));

	std::unique_ptr<Customer> customer2 = std::make_unique<Customer>(false, std::move(*birthDate2));

	customerQueue->Enqueue(std::move(*customer));

	mailOfficial->getMediator()->CallCustomer(*customer);

	customerQueue->Dequeue();

	customerQueue->Enqueue(std::move(*customer2));

	mailOfficial->getMediator()->CallCustomer(*customer2);

	customerQueue->Dequeue();

	return 0;
}


