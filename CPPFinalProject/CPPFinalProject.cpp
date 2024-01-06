// CPPFinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Customer.h";
#include "CustomerQueue.h"
#include "MailActions.h"
#include <iostream>

int main()
{
	std::unique_ptr<CustomerQueue> customerQueue = std::make_unique<CustomerQueue>();

	std::unique_ptr<DateOfBirth> birthDate = std::make_unique<DateOfBirth>(5,11,1998);
	std::unique_ptr<DateOfBirth> birthDate2 = std::make_unique<DateOfBirth>(5, 11, 1998);

	std::unique_ptr<Customer> customer = std::make_unique<Customer>(true, std::move(*birthDate));

	std::unique_ptr<Customer> customer2 = std::make_unique<Customer>(true, std::move(*birthDate2));

	customerQueue->Enqueue(std::move(*customer));

	customerQueue->Enqueue(std::move(*customer2));

	customerQueue->Dequeue();

	return 0;
}


