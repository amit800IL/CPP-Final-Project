#include "MailCustomerCommunication.h"

MailCustomerCommunication::MailCustomerCommunication(const std::vector<std::shared_ptr<MailClerk>>& clerks)
	: clerks(clerks) {}

void MailCustomerCommunication::CallCustomer(const Customer& customer)
{
	bool isCustomerServed = false;
	bool isAnyClerkAvailable = false;

	while (!isCustomerServed)
	{
		MailActions chosenAction = MakingAction();

		shared_ptr<MailClerk> clerk = FindAvailableClerk(chosenAction);

		ofstream customerFile("CustomerData.txt", ios::app);

		if (customerFile.is_open()) 
		{
			customer.Print(customerFile);

			customerFile.close();
		}

		if (clerk != nullptr)
		{
			MailActions action = GetAvailableAction(*clerk);

			if (action != MailActions::None)
			{
				clerk->PerformAction(chosenAction);
				clerk->SetBusy();
				isCustomerServed = true;
				isAnyClerkAvailable = true;
				break;
			}

			else
			{
				cout << "Invalid action for this clerk. Please choose again." << endl;
			}

		}

		if (!isAnyClerkAvailable)
		{
			for (const shared_ptr<MailClerk>& clerk : clerks)
			{
				clerk->SetAvailable();
			}
		}
	}
}

MailActions MailCustomerCommunication::MakingAction() const
{
	char input = '0';

	cout << "Choose an action:" << endl;

	cout << "1. Receive a package" << endl;
	cout << "2. Deliver a package" << endl;
	cout << "3. Make a payment" << endl;
	cout << "4. Purchase a product" << endl;

	cin >> input;

	switch (input)
	{
	case '1':
		return MailActions::RecivePackage;
	case '2':
		return MailActions::DeliverPackage;
	case '3':
		return MailActions::MakePayment;
	case '4':
		return MailActions::PurchaseProduct;
	}

}


MailActions MailCustomerCommunication::GetAvailableAction(const MailClerk& clerk) const
{
	for (MailActions action : {MailActions::RecivePackage, MailActions::DeliverPackage,
		MailActions::MakePayment, MailActions::PurchaseProduct})
	{
		if (clerk.CanHandleAction(action))
		{
			return action;
		}
	}
	return MailActions::None;
}

shared_ptr<MailClerk> MailCustomerCommunication::FindAvailableClerk(MailActions& action) const
{
	for (const shared_ptr<MailClerk>& clerk : clerks)
	{
		if (clerk->IsAvailable() && clerk->CanHandleAction(action))
		{
			cout << *clerk << endl;
			return clerk;
		}
	}

	cout << "Not available clerk found for that action" << endl;
	return nullptr;
}
