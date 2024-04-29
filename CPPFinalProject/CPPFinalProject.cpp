
#include "Customer.h";
#include "CustomerQueue.h"
#include "CustomerQueueIterator.h"
#include "MailClerk.h"
#include "MailCustomerCommunication.h"
#include "STLCustomerQueue.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
using namespace std;

void PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
void UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
void BaseSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);
void CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);
unique_ptr<Customer> CreateCustomer();

int main()
{
	vector<shared_ptr<MailClerk>> clerks;

	unordered_set<MailActions> clerk1Actions = { MailActions::RecivePackage, MailActions::MakePayment,  MailActions::DeliverPackage, MailActions::PurchaseProduct };
	unordered_set<MailActions> clerk2Actions = { MailActions::RecivePackage, MailActions::MakePayment , MailActions::PurchaseProduct };
	unordered_set<MailActions> clerk3Actions = { MailActions::PurchaseProduct, MailActions::MakePayment };
	unordered_set<MailActions> clerk4Actions = { MailActions::RecivePackage, MailActions::DeliverPackage };

	shared_ptr<MailClerk> mailClerk1 = make_shared<MailClerk>(1, clerk1Actions);
	shared_ptr<MailClerk> mailClerk2 = make_shared<MailClerk>(2, clerk2Actions);
	shared_ptr<MailClerk> mailClerk3 = make_shared<MailClerk>(3, clerk3Actions);
	shared_ptr<MailClerk> mailClerk4 = make_shared<MailClerk>(4, clerk4Actions);

	clerks.push_back(mailClerk1);
	clerks.push_back(mailClerk2);
	clerks.push_back(mailClerk3);
	clerks.push_back(mailClerk4);

	shared_ptr<MailCustomerCommunication> mailActionsManager = make_shared<MailCustomerCommunication>(clerks);

	char input = ' ';

	PickAndUseSystem(input, mailActionsManager);

	return 0;
}

void PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager)
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
			cout << "Customers inserted" << endl;
		}
	}

	UseSytem(input, mailActionsManager);
}

void UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager)
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

void BaseSTL(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	unique_ptr<STLCustomerQueue> stlCustomerQueue = make_unique<STLCustomerQueue>();

	unique_ptr<DateOfBirth> birthDate1 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(10, 9, 2010);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(11, 10, 2007);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate5 = make_unique<DateOfBirth>(5, 6, 1950);
	unique_ptr<DateOfBirth> birthDate6 = make_unique<DateOfBirth>(17, 3, 1950);
	unique_ptr<DateOfBirth> birthDate7 = make_unique<DateOfBirth>(17, 3, 1940);
	unique_ptr<DateOfBirth> birthDate8 = make_unique<DateOfBirth>(17, 3, 2010);

	unique_ptr<Customer> customer1 = make_unique<RegularCustomer>(*birthDate1);
	unique_ptr<Customer> customer2 = make_unique<RegularCustomer>(*birthDate2);
	unique_ptr<Customer> customer3 = make_unique<RegularCustomer>(*birthDate3);
	unique_ptr<Customer> customer4 = make_unique<RegularCustomer>(*birthDate4);
	unique_ptr<Customer> customer5 = make_unique<ElderlyCustomer>(*birthDate5);
	unique_ptr<Customer> customer6 = make_unique<ElderlyCustomer>(*birthDate6);
	unique_ptr<Customer> customer7 = make_unique<ElderlyCustomer>(*birthDate7);
	unique_ptr<Customer> customer8 = make_unique<ElderlyCustomer>(*birthDate8);

	stlCustomerQueue->PlaceCustomerInQueue(move(customer1));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer2));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer3));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer4));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer5));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer6));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer7));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer8));

	stlCustomerQueue->GetCustomersFromQueue(mailActionsManager);
}

void CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	shared_ptr<CustomerQueue> customerQueue = make_shared<CustomerQueue>();

	int queueSize = 3;
	vector<unique_ptr<Customer>> customers;

	for (int i = 0; i < queueSize; i++)
	{
		unique_ptr<Customer> customer = CreateCustomer();
		if (customer != nullptr)
		{
			customers.push_back(move(customer));
		}
	}

	for (auto& customer : customers)
	{
		customerQueue->Enqueue(move(customer));
	}

	// Serve customers from the queue
	customerQueue->ServeCustomer(mailActionsManager);
}

unique_ptr<Customer> CreateCustomer()
{
	int day, month, year;

	cout << "Enter Customer Birthdate (DD MM YYYY): ";
	cin >> day >> month >> year;

	unique_ptr<DateOfBirth> birthDate = make_unique<DateOfBirth>(day, month, year);

	if (birthDate->CalcualteAge() >= 65)
	{
		return make_unique<ElderlyCustomer>(*birthDate);

	}
	else
	{
		return make_unique<RegularCustomer>(*birthDate);
	}

	cout << "No customer inserted" << endl;
	return nullptr;
}


