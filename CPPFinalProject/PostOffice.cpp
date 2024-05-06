#include "PostOffice.h"


PostOffice::PostOffice()
{
	vector<shared_ptr<MailClerk>> clerks;

	vector<MailActions> clerk1Actions = { MailActions::ReceivePackage, MailActions::MakePayment,  MailActions::DeliverPackage, MailActions::PurchaseProduct };
	vector<MailActions> clerk2Actions = { MailActions::ReceivePackage, MailActions::MakePayment , MailActions::PurchaseProduct };
	vector<MailActions> clerk3Actions = { MailActions::PurchaseProduct, MailActions::MakePayment };
	vector<MailActions> clerk4Actions = { MailActions::ReceivePackage, MailActions::DeliverPackage };

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
}

void PostOffice::PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager)
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

void PostOffice::UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager)
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

void PostOffice::BaseSTL(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	unique_ptr<STLCustomerQueue> stlCustomerQueue = make_unique<STLCustomerQueue>();

	int queueSize = 3;
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
		stlCustomerQueue->Enqueue(move(customer));
	}


	stlCustomerQueue->ServeCustomer(mailActionsManager);
}

void PostOffice::CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	unique_ptr<CustomerQueue> customerQueue = make_unique<CustomerQueue>();

	int queueSize = 3;
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
	}

	customerQueue->ServeCustomer(mailActionsManager);
}