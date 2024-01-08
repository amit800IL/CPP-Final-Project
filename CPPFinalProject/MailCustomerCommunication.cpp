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

	std::cout << "Choose which action you want to do " << std::endl;
	std::cout << "1. i want to receive a package " << std::endl;
	std::cout << "2. i want to deliever a package " << std::endl;
	std::cout << "3. i want to make a payment" << std::endl;
	std::cout << "4. i want to purchase a product " << std::endl;

	do
	{
		std::cin >> input;

		switch (input)
		{
		case '1':
			std::cout << "Here is your pachage" << std::endl;
			hasCustomerBeenServed = true;
			break;
		case '2':
			std::cout << "Your package has been sent" << std::endl;
			hasCustomerBeenServed = true;
			break;
		case '3':
			std::cout << "Your payment has been made" << std::endl;
			hasCustomerBeenServed = true;
			break;
		case '4':
			std::cout << "here is your product" << std::endl;
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