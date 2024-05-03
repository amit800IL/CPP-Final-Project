
#include "MailCustomerCommunication.h"

MailCustomerCommunication::MailCustomerCommunication(const vector<shared_ptr<MailClerk>>& clerks)
	: clerks(clerks) {}

void MailCustomerCommunication::CallCustomer(const Customer& customer)
{
	bool isCustomerServed = false;

	while (!isCustomerServed)
	{
		MailActions chosenAction = customer.GetCustomerAction();

		shared_ptr<MailClerk> clerk = FindAvailableClerk(chosenAction);

		ofstream customerFile("CustomerData.txt", ios::app);

		if (customerFile.is_open())
		{
			customer.Print(customerFile);

			customerFile.close();
		}

		if (clerk != nullptr)
		{
			MailActions action = GetAvailableAction(clerk);

			if (action != MailActions::None)
			{
				clerk->PerformAction(chosenAction);
				isCustomerServed = true;
				break;

			}

			else
			{
				cout << "Invalid action for this clerk. Please choose again." << endl;
			}

		}
	}
}

MailActions MailCustomerCommunication::ChooseAction()
{
	char input = '0';

	cout << "Choose an action:" << endl;

	cout << "1. Receive a package" << endl;
	cout << "2. Deliver a package" << endl;
	cout << "3. Make a payment" << endl;
	cout << "4. Purchase a product" << endl;

	cin >> input;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (input)
	{
	case '1':
		return MailActions::ReceivePackage;
	case '2':
		return MailActions::DeliverPackage;
	case '3':
		return MailActions::MakePayment;
	case '4':
		return MailActions::PurchaseProduct;
	}
}


MailActions MailCustomerCommunication::GetAvailableAction(const shared_ptr<MailClerk>& clerk) const
{
	for (MailActions action : {MailActions::ReceivePackage, MailActions::DeliverPackage,
		MailActions::MakePayment, MailActions::PurchaseProduct})
	{
		if (clerk->CanHandleAction(action))
		{
			return action;
		}
	}
	return MailActions::None;
}

shared_ptr<MailClerk> MailCustomerCommunication::FindAvailableClerk(const MailActions& action) const
{
	for (const shared_ptr<MailClerk>& clerk : clerks)
	{
		if (clerk->IsAvailable() && clerk->CanHandleAction(action))
		{
			clerk->Print(cout);
			return clerk;
		}
	}

	cout << "Not available clerk found for that action" << endl;
	return nullptr;
}

unique_ptr<Customer> MailCustomerCommunication::CreateCustomer()
{
	string input;
	int day, month, year;

	cout << "Enter Customer Birthdate (DD/MM/YYYY): ";
	getline(cin, input);

	stringstream ss(input);
	char slash;
	if (ss >> day >> slash >> month >> slash >> year)
	{
		MailActions chosenAction = ChooseAction();

		unique_ptr<DateOfBirth> birthDate = make_unique<DateOfBirth>(day, month, year);

		if (birthDate->CalcualteAge() >= 65) 
		{
		   unique_ptr<Customer> customer = make_unique<ElderlyCustomer>(*birthDate, chosenAction);

		   return customer;
		}
		else 
		{
			unique_ptr<Customer> customer = make_unique<RegularCustomer>(*birthDate, chosenAction);

			return customer;
		}
	}

	cerr << "Invalid date format. Please enter in the format DD/MM/YYYY." << endl;
	return nullptr;
}