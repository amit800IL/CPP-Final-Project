
#include "MailCustomerCommunication.h"

MailCustomerCommunication::MailCustomerCommunication(const vector<shared_ptr<MailClerk>>& clerks)
	: clerks(clerks) {}

void MailCustomerCommunication::CallCustomer(const Customer& customer)
{
	bool isCustomerServed = false;

	MailActions chosenAction = customer.GetCustomerAction();
	shared_ptr<MailClerk> clerk = FindAvailableClerk(chosenAction);

	while (!isCustomerServed)
	{
		if (chosenAction == MailActions::Cancel)
			break;

		ofstream customerFile("CustomerData.txt", ios::app);

		if (customerFile.is_open())
		{
			customer.Print(customerFile);

			customerFile.close();
		}

		if (clerk != nullptr)
		{
			clerk->PerformAction(chosenAction);
			isCustomerServed = true;
			break;
		}
		else
		{
			break;
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
	cout << "5. Give up your place in the queue" << endl;

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
	case '5':
		return MailActions::Cancel;
	}
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

	cout << "No availabile clerk found for your requested action" << endl;

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

		if (birthDate != nullptr)
		{
			if (birthDate->CalcualteAge() >= 65)
			{
				for (const shared_ptr<MailClerk>& clerk : clerks)
				{
					if (clerk != nullptr && clerk->CanHandleAction(chosenAction))
					{
						return make_unique<ElderlyCustomer>(*birthDate, chosenAction, clerk);
					}
				}
			}

			else
			{
				for (const shared_ptr<MailClerk>& clerk : clerks)
				{
					if (clerk != nullptr && clerk->CanHandleAction(chosenAction))
					{
						return make_unique<RegularCustomer>(*birthDate, chosenAction, clerk);
					}
				}
			}
		}

	}

	cerr << "Invalid date format or no suitable clerk found for the chosen action." << endl;
	return nullptr;
}

vector<shared_ptr<MailClerk>> MailCustomerCommunication::GetClerksList()
{
	return clerks;
}
