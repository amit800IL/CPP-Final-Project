
#include "MailCustomerCommunication.h"

MailCustomerCommunication::MailCustomerCommunication(const vector<shared_ptr<MailClerk>>& clerks)
	: clerks(clerks) {}

void MailCustomerCommunication::CallCustomer(const Customer& customer)
{
	bool isCustomerServed = false;

	//Gets the customer's chosen action

	MailActions chosenAction = customer.GetCustomerAction();

	//Finds the available clerk for that action

	shared_ptr<MailClerk> clerk = FindAvailableClerk(chosenAction);

	while (!isCustomerServed)
	{
		//If the customer choose to cancel it just goes away to atlantis apparently, or something like that

		if (chosenAction == MailActions::Cancel)
			break;

		//Creates the CusomterData file, or find it if it exists

		ofstream customerFile("CustomerData.txt", ios::app);

		if (customerFile.is_open())
		{
			//Writes the customer data into the file

			customer.Print(customerFile);

			customerFile.close();
		}

		if (clerk != nullptr)
		{
			//If clerk exists, the clerk perfomed the requested action by the customer

			clerk->PerformAction(chosenAction);

			//Sets the bool of isCustomerServed to true, so it will not stay on the loop for that customer and clerk

			isCustomerServed = true;
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
	string name;
	cout << "Enter Customer Name: ";
	getline(cin, name);

	string input;
	int day, month, year;

	cout << "Enter Customer Birthdate (DD/MM/YYYY or DD.MM.YYYY): ";
	getline(cin, input);

	stringstream stringInput(input);
	char slash;
	if (stringInput >> day >> slash >> month >> slash >> year)
	{
		MailActions chosenAction = ChooseAction();
		unique_ptr<DateOfBirth> birthDate = make_unique<DateOfBirth>(day, month, year);

		if (birthDate != nullptr)
		{
			//Checks if customer is elderly

			if (birthDate->CalcualteAge() >= 65)
			{
				//Goes through the list of clerks, to find a matching clerk for the customer's requested action

				for (const shared_ptr<MailClerk>& clerk : clerks)
				{
					if (clerk != nullptr && clerk->CanHandleAction(chosenAction))
					{
						//If the clerk exists and can handle an action, it returns the new customer

						return make_unique<ElderlyCustomer>(name, *birthDate, chosenAction, clerk);
					}
				}
			}

			//Checks if customer is regular

			else
			{
				for (const shared_ptr<MailClerk>& clerk : clerks)
				{
					//Goes through the list of clerks, to find a matching clerk for the customer's requested action

					if (clerk != nullptr && clerk->CanHandleAction(chosenAction))
					{
						//If the clerk exists and can handle an action, it returns the new customer

						return make_unique<RegularCustomer>(name, *birthDate, chosenAction, clerk);
					}
				}
			}
		}

	}

	return nullptr;
}

vector<shared_ptr<MailClerk>> MailCustomerCommunication::GetClerksList()
{
	return clerks;
}

void MailCustomerCommunication::CalculateServiceDuration()
{
	//Sets the time to the current hour and minute

	serviceHour = chrono::system_clock::now();

	//Makes the system sleep for one second to create the waiting

	this_thread::sleep_for(chrono::seconds(1));

	//Sets a new local variable, end time, to calculate the waiting time

	chrono::time_point<chrono::system_clock> endTime = chrono::system_clock::now();

	//Calcuates the waiting time by subtracting the end time from the actual time tht customer was served

	waitingTime = endTime - serviceHour;

	//Sets the service hour to calender time

	time_t timeServedTimeTConverstion = chrono::system_clock::to_time_t(serviceHour);
	
	//Convers the calender time to local hour and minute

	tm* timeServedLocalTimeConvertion = localtime(&timeServedTimeTConverstion);

	//Displays the data

	cout << "Customer was served at: "  << put_time(timeServedLocalTimeConvertion, "%H:%M") << std::endl;

	cout << "Waiting Time: " << static_cast<int>(waitingTime.count()) << " minutes" << endl;

	cout << "--------------------------------------------------------" << endl;
}
