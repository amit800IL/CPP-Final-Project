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
	std::shared_ptr<IServiceCustomerMediator> mailActionsManager = std::make_shared<ServiceCustomerCommunication>();

	std::unique_ptr<MailOfficial> mailOfficial = std::make_unique<MailOfficial>(mailActionsManager);

	std::unique_ptr<CustomerQueue> customerQueue = std::make_unique<CustomerQueue>();

	std::unique_ptr<DateOfBirth> birthDate = std::make_unique<DateOfBirth>(11,12,1998);
	std::unique_ptr<DateOfBirth> birthDate2 = std::make_unique<DateOfBirth>(17,3,1955);

	std::unique_ptr<Customer> customer = std::make_unique<Customer>(std::move(*birthDate));

	std::unique_ptr<Customer> customer2 = std::make_unique<Customer>(std::move(*birthDate2));

	customerQueue->Enqueue(std::move(*customer));

	mailActionsManager->CallCustomer(*customer, &IServiceCustomerMediator::MakingAction);

	customerQueue->Dequeue();

	customerQueue->Enqueue(std::move(*customer2));

	mailActionsManager->CallCustomer(*customer2, &IServiceCustomerMediator::MakingAction);

	customerQueue->Dequeue();

	return 0;
}


