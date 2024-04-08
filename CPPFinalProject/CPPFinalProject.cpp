
#include "Customer.h";
#include "CustomerQueue.h"
#include "CustomerQueueIterator.h"
#include "MailActions.h"
#include "MailCustomerCommunication.h"
#include "MailOfficial.h"
#include "STLCustomerQueue.h"
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <queue>

using namespace std;

void PickAndUseSystem(char input, shared_ptr<IServiceCustomerMediator> mailActionsManager);
void UseSytem(char input, shared_ptr<IServiceCustomerMediator> mailActionsManager);
void BaseSTL(shared_ptr<IServiceCustomerMediator> mailActionsManager);
void CustomSTL(shared_ptr<IServiceCustomerMediator> mailActionsManager);

int main()
{
	shared_ptr<IServiceCustomerMediator> mailActionsManager = make_shared<MailCustomerCommunication>();

	unique_ptr<DateOfBirth> birthDate = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(17, 3, 1950);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(17, 3, 1940);

	char input = ' ';

	PickAndUseSystem(input, mailActionsManager);

	return 0;
}

void PickAndUseSystem(char input, shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
	cout << "Hello, welcome to your line managment system, please choose the system you want to use: " << endl;

	cout << "1.Use basic line managment system(STL)" << endl;
	cout << "2.Use custom line managment system(custom STL)" << endl;

	while (input != '1' && input != '2')
	{
		cin >> input;

		if (input == '1')
		{
			cout << "Customers inserted" << endl;
		}
		else if (input == '2')
		{
			cout << "Good choice, here are the customers that are waiting: " << endl;
		}
	}

	UseSytem(input, mailActionsManager);
}

void UseSytem(char input, shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
	if (input == '1')
	{
		BaseSTL(mailActionsManager);
	}

	else if (input == '2')
	{
		CustomSTL(mailActionsManager);
	}
}

void BaseSTL(shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
	unique_ptr<STLCustomerQueue> stlCustomerQueue = make_unique<STLCustomerQueue>();

	unique_ptr<DateOfBirth> birthDate = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(17, 3, 1950);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(17, 3, 1940);
	unique_ptr<DateOfBirth> birthDate5 = make_unique<DateOfBirth>(5, 6, 1950);
	unique_ptr<DateOfBirth> birthDate6 = make_unique<DateOfBirth>(10, 9, 2010);
	
	unique_ptr<Customer> customer = make_unique<RegularCustomer>(*birthDate);
	unique_ptr<Customer> customer2 = make_unique<ElderlyCustomer>(*birthDate2);
	unique_ptr<Customer> customer3 = make_unique<RegularCustomer>(*birthDate3);
	unique_ptr<Customer> customer4 = make_unique<ElderlyCustomer>(*birthDate4);
	unique_ptr<Customer> customer5 = make_unique<ElderlyCustomer>(*birthDate5);
	unique_ptr<Customer> customer6 = make_unique<RegularCustomer>(*birthDate6);

	stlCustomerQueue->PlaceCustomerInQueue(move(customer));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer2));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer3));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer4));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer5));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer6));

	stlCustomerQueue->GetCustomersFromQueue(mailActionsManager);
}

void CustomSTL(shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
	shared_ptr<CustomerQueue> customerQueue = make_shared<CustomerQueue>();

	unique_ptr<DateOfBirth> birthDate = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(17, 3, 1950);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(17, 3, 1940);

	unique_ptr<Customer> customer = make_unique<RegularCustomer>(*birthDate);
	unique_ptr<Customer> customer2 = make_unique<ElderlyCustomer>(*birthDate2);
	unique_ptr<Customer> customer3 = make_unique<RegularCustomer>(*birthDate3);
	unique_ptr<Customer> customer4 = make_unique<ElderlyCustomer>(*birthDate4);

	customerQueue->Enqueue(move(*customer));
	customerQueue->Enqueue(move(*customer2));
	customerQueue->Enqueue(move(*customer3));
	customerQueue->Enqueue(move(*customer4));

	while (!customerQueue->IsEmpty())
	{
		CustomerQueueIterator customerIterator = customerQueue->begin();
		Customer& customer = *customerIterator;
		mailActionsManager->CallCustomer(customer);
		customerQueue->Dequeue();
	}
}
