#include "MailCustomerCommunication.h"

MailCustomerCommunication::MailCustomerCommunication(const std::vector<std::shared_ptr<MailClerk>>& clerks)
	: clerks(clerks) {}

void MailCustomerCommunication::CallCustomer(Customer& customer)
{
	bool customerServed = false;

	for (shared_ptr<MailClerk>& clerk : clerks)
	{
		MailActions action = GetAvailableAction(*clerk);

		if (action != MailActions::None)
		{
			while (!customerServed)
			{
				MailActions chosenAction = MakingAction(*clerk);

				if (clerk->canHandleAction(chosenAction))
				{
					clerk->PerformAction(chosenAction);
					customerServed = true;
					break;
				}
				else
				{
					cout << "Invalid action for this clerk. Please choose again." << endl;
				}
			}

			customerServed = false;
		}
	}
}

MailActions MailCustomerCommunication::MakingAction(const MailClerk& clerk) const
{
	char input = '0';

	cout << "Choose an action:" << endl;

	if (clerk.canHandleAction(MailActions::RecivePackage))
		cout << "1. Receive a package" << endl;

	if (clerk.canHandleAction(MailActions::DeliverPackage))
		cout << "2. Deliver a package" << endl;

	if (clerk.canHandleAction(MailActions::MakePayment))
		cout << "3. Make a payment" << endl;

	if (clerk.canHandleAction(MailActions::PurchaseProduct))
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

MailActions MailCustomerCommunication::MakingAction()
{
	return MailActions();
}

MailActions MailCustomerCommunication::GetAvailableAction(const MailClerk& clerk) const
{
	for (MailActions action : {MailActions::RecivePackage, MailActions::DeliverPackage,
		MailActions::MakePayment, MailActions::PurchaseProduct})
	{
		if (clerk.canHandleAction(action))
		{
			return action;
		}
	}
	return MailActions::None;
}