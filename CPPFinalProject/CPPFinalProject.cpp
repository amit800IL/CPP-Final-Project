// CPPFinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Customer.h";
#include "CustomerQueue.h"
#include "MailActions.h"
#include "MailCustomerCommunication.h"
#include "MailOfficial.h"
#include <iostream>

int main()
{
	std::shared_ptr<IServiceCustomerMediator> mailActionsManager = std::make_shared<MailCustomerCommunication>();

	std::unique_ptr<MailOfficial> mailOfficial = std::make_unique<MailOfficial>();

	std::shared_ptr<CustomerQueue> customerQueue = std::make_shared<CustomerQueue>();

	std::unique_ptr<DateOfBirth> birthDate = std::make_unique<DateOfBirth>(11, 12, 1998);
	std::unique_ptr<DateOfBirth> birthDate2 = std::make_unique<DateOfBirth>(17, 3, 1955);
	std::unique_ptr<DateOfBirth> birthDate3 = std::make_unique<DateOfBirth>(3, 1, 2000);
	std::unique_ptr<DateOfBirth> birthDate4 = std::make_unique<DateOfBirth>(17, 3, 1940);

	std::unique_ptr<Customer> customer = std::make_unique<RegularCustomer>(*birthDate);

	std::unique_ptr<Customer> customer2 = std::make_unique<ElderlyCustomer>(*birthDate2);

	std::unique_ptr<Customer> customer3 = std::make_unique<RegularCustomer>(*birthDate3);

	std::unique_ptr<Customer> customer4 = std::make_unique<ElderlyCustomer>(*birthDate4);

	customerQueue->Enqueue(std::move(*customer));
	customerQueue->Enqueue(std::move(*customer2));
	customerQueue->Enqueue(std::move(*customer3));
	customerQueue->Enqueue(std::move(*customer4));


	for (auto it = customerQueue->begin(); it != customerQueue->end(); ++it)
	{
		Customer& customer = *it;

		// Store information about which customer to serve
		bool serveElderly = customer.IsElderlyCustomer() && !customerQueue->LastCustomerRegular();

		mailActionsManager->CallCustomer(customer, &IServiceCustomerMediator::MakingAction);

		// Output the serving message based on the stored information
		if (serveElderly)
		{
			std::cout << "Serving elderly customer: " << customer << std::endl;
		}
		else
		{
			std::cout << "Serving regular customer: " << customer << std::endl;

		}
	}

			if (!customerQueue->IsEmpty())
			{
				customerQueue->Dequeue();
			}
	// Dequeue the appropriate customer after the iteration
	return 0;
}

