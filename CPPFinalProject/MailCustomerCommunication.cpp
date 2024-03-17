#include "MailCustomerCommunication.h"

void MailCustomerCommunication::CallCustomer(Customer& customer, void (IServiceCustomerMediator::* MakingAction)())
{
	int customerNumber = customer.GetCustomerNumber();

	if (customerNumber)
	{
		std::cout << " Customer " << customerNumber << " has been called " << std::endl;
		this->MakingAction();
	}
}

void MailCustomerCommunication::MakingAction()
{
	char input = '0';

	bool hasCustomerBeenServed = false;

	cout << "Choose which action you want to do " << endl;
	cout << "1. i want to receive a package " << endl;
	cout << "2. i want to deliever a package " << endl;
	cout << "3. i want to make a payment" << endl;
	cout << "4. i want to purchase a product " << endl;

	do
	{
		std::cin >> input;

		switch (input)
		{
		case '1':
			cout << "Here is your pachage" << endl;
			hasCustomerBeenServed = true;
			break;
		case '2':
			cout << "Your package has been sent" << endl;
			hasCustomerBeenServed = true;
			break;
		case '3':
			cout << "Your payment has been made" << endl;
			hasCustomerBeenServed = true;
			break;
		case '4':
			cout << "here is your product" << endl;
			hasCustomerBeenServed = true;
			break;
		default:
			break;
		}

		if (hasCustomerBeenServed)
		{
			break;
		}

	} while ((input != 'q' && input != 'Q'));
}