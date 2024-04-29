
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

	vector<MailActions> clerk1Actions = { MailActions::RecivePackage, MailActions::MakePayment,  MailActions::DeliverPackage, MailActions::PurchaseProduct };
	vector<MailActions> clerk2Actions = { MailActions::RecivePackage, MailActions::MakePayment , MailActions::PurchaseProduct };
	vector<MailActions> clerk3Actions = { MailActions::PurchaseProduct, MailActions::MakePayment };
	vector<MailActions> clerk4Actions = { MailActions::RecivePackage, MailActions::DeliverPackage };

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

	for (unique_ptr<Customer>& customer : customers)
	{
		stlCustomerQueue->PlaceCustomerInQueue(move(customer));
	}

	stlCustomerQueue->GetCustomersFromQueue(mailActionsManager);
}

void CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	unique_ptr<CustomerQueue> customerQueue = make_unique<CustomerQueue>();

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

	for (unique_ptr<Customer>& customer : customers)
	{
		customerQueue->Enqueue(move(customer));
	}

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


