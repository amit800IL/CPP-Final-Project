// CPPFinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Customer.h";
#include "CustomerQueue.h"
#include "MailActions.h"
#include <iostream>

int main()
{
	std::unique_ptr<CustomerQueue> customerQueue = std::make_unique<CustomerQueue>();

	std::unique_ptr<Customer> customer = std::make_unique<Customer>();

	std::unique_ptr<Customer> customer2 = std::make_unique<Customer>();

	customerQueue->Enqueue(*customer);

	customerQueue->Enqueue(*customer2);

	customerQueue->Dequeue();

	return 0;
}


