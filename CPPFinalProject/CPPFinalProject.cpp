
#include "Customer.h";
#include "CustomerQueue.h"
#include "MailClerk.h"
#include "MailCustomerCommunication.h"
#include "STLCustomerQueue.h"
#include <sstream>

using namespace std;

void PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
void UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
void BaseSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);
void CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);

int main()
{
	vector<shared_ptr<MailClerk>> clerks;

	vector<MailActions> clerk1Actions = { MailActions::ReceivePackage, MailActions::MakePayment,  MailActions::DeliverPackage, MailActions::PurchaseProduct };
	//vector<MailActions> clerk2Actions = { MailActions::ReceivePackage, MailActions::MakePayment , MailActions::PurchaseProduct };
	//vector<MailActions> clerk3Actions = { MailActions::PurchaseProduct, MailActions::MakePayment };
	//vector<MailActions> clerk4Actions = { MailActions::ReceivePackage, MailActions::DeliverPackage };

	shared_ptr<MailClerk> mailClerk1 = make_shared<MailClerk>(1, clerk1Actions);
	//shared_ptr<MailClerk> mailClerk2 = make_shared<MailClerk>(2, clerk2Actions);
	//shared_ptr<MailClerk> mailClerk3 = make_shared<MailClerk>(3, clerk3Actions);
	//shared_ptr<MailClerk> mailClerk4 = make_shared<MailClerk>(4, clerk4Actions);

	clerks.push_back(mailClerk1);
	//clerks.push_back(mailClerk2);
	//clerks.push_back(mailClerk3);
	//clerks.push_back(mailClerk4);

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

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

	/*int queueSize = 5;
	vector<unique_ptr<Customer>> customers;

	for (int i = 0; i < queueSize; i++)
	{
		unique_ptr<Customer> customer = mailActionsManager->CreateCustomer();

		if (customer != nullptr)
		{
			customers.push_back(move(customer));
		}
	}

	for (unique_ptr<Customer>& customer : customers)
	{
		stlCustomerQueue->PlaceCustomerInQueue(move(customer));
	}*/

	unique_ptr<DateOfBirth> birthDate1 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(10, 9, 2010);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(11, 10, 2007);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate5 = make_unique<DateOfBirth>(5, 6, 1910);
	unique_ptr<DateOfBirth> birthDate6 = make_unique<DateOfBirth>(17, 3, 1905);
	unique_ptr<DateOfBirth> birthDate7 = make_unique<DateOfBirth>(17, 3, 1920);
	unique_ptr<DateOfBirth> birthDate8 = make_unique<DateOfBirth>(17, 3, 1930);

	unique_ptr<Customer> customer1 = make_unique<RegularCustomer>(*birthDate1, MailActions::PurchaseProduct);
	unique_ptr<Customer> customer2 = make_unique<RegularCustomer>(*birthDate2, MailActions::MakePayment);
	unique_ptr<Customer> customer3 = make_unique<RegularCustomer>(*birthDate3, MailActions::DeliverPackage);
	unique_ptr<Customer> customer4 = make_unique<RegularCustomer>(*birthDate4, MailActions::ReceivePackage);
	unique_ptr<Customer> customer5 = make_unique<ElderlyCustomer>(*birthDate5, MailActions::DeliverPackage);
	unique_ptr<Customer> customer6 = make_unique<ElderlyCustomer>(*birthDate6, MailActions::MakePayment);
	unique_ptr<Customer> customer7 = make_unique<ElderlyCustomer>(*birthDate7, MailActions::PurchaseProduct);
	unique_ptr<Customer> customer8 = make_unique<ElderlyCustomer>(*birthDate8, MailActions::ReceivePackage);

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
	unique_ptr<CustomerQueue> customerQueue = make_unique<CustomerQueue>();

	/*int queueSize = 3;
	vector<unique_ptr<Customer>> customers;

	for (int i = 0; i < queueSize; i++)
	{
		unique_ptr<Customer> customer = mailActionsManager->CreateCustomer();

		if (customer != nullptr)
		{
			customers.push_back(move(customer));
		}
	}

	for (unique_ptr<Customer>& customer : customers)
	{
		customerQueue->Enqueue(move(customer));
	}*/

	unique_ptr<DateOfBirth> birthDate1 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(10, 9, 2010);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(11, 10, 2007);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate5 = make_unique<DateOfBirth>(5, 6, 1910);
	unique_ptr<DateOfBirth> birthDate6 = make_unique<DateOfBirth>(17, 3, 1905);
	unique_ptr<DateOfBirth> birthDate7 = make_unique<DateOfBirth>(17, 3, 1920);
	unique_ptr<DateOfBirth> birthDate8 = make_unique<DateOfBirth>(17, 3, 1930);

	unique_ptr<Customer> customer1 = make_unique<RegularCustomer>(*birthDate1, MailActions::PurchaseProduct);
	unique_ptr<Customer> customer2 = make_unique<RegularCustomer>(*birthDate2, MailActions::MakePayment);
	unique_ptr<Customer> customer3 = make_unique<RegularCustomer>(*birthDate3, MailActions::DeliverPackage);
	unique_ptr<Customer> customer4 = make_unique<RegularCustomer>(*birthDate4, MailActions::ReceivePackage);
	unique_ptr<Customer> customer5 = make_unique<ElderlyCustomer>(*birthDate5, MailActions::MakePayment);
	unique_ptr<Customer> customer6 = make_unique<ElderlyCustomer>(*birthDate6, MailActions::DeliverPackage);
	unique_ptr<Customer> customer7 = make_unique<ElderlyCustomer>(*birthDate7, MailActions::PurchaseProduct);
	unique_ptr<Customer> customer8 = make_unique<ElderlyCustomer>(*birthDate8, MailActions::MakePayment);

	customerQueue->Enqueue(move(customer1));
	customerQueue->Enqueue(move(customer2));
	customerQueue->Enqueue(move(customer3));
	customerQueue->Enqueue(move(customer4));
	customerQueue->Enqueue(move(customer5));
	customerQueue->Enqueue(move(customer6));
	customerQueue->Enqueue(move(customer7));
	customerQueue->Enqueue(move(customer8));

	customerQueue->ServeCustomer(mailActionsManager);
}



