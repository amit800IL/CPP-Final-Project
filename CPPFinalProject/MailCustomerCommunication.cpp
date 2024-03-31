#include "MailCustomerCommunication.h"

void MailCustomerCommunication::CallCustomer(Customer& customer)
{
	int customerNumber = customer.GetCustomerNumber();

	if (customerNumber)
	{
		std::cout << " Customer " << customerNumber << " has been called " << std::endl;
		MakingAction();
	}
}

MailActions MailCustomerCommunication::MakingAction()
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
		cin >> input;

		switch (input)
		{
		case '1': return MailActions::RecivePackage;
		case '2': return MailActions::DeliverPackage;
		case '3': return MailActions::MakePayment;
		case '4': return MailActions::PurchaseProduct;
		}

		if (hasCustomerBeenServed)
		{
			break;
		}

	} while ((input != 'q' && input != 'Q'));
}