#include "MailCustomerCommunication.h"

MailCustomerCommunication::MailCustomerCommunication(const std::vector<std::shared_ptr<MailClerk>>& clerks)
	: clerks(clerks) {}

void MailCustomerCommunication::CallCustomer(Customer& customer)
{
	bool isCustomerServed = false;

	for (shared_ptr<MailClerk>& clerk : clerks)
	{
		if (clerk->IsAvailable())
		{
			while (!isCustomerServed)
			{
				MailActions action = GetAvailableAction(*clerk);

				if (action != MailActions::None)
				{
					MailActions chosenAction = MakingAction(*clerk);

					if (clerk->CanHandleAction(chosenAction))
					{
						clerk->PerformAction(chosenAction);
						isCustomerServed = true;
						clerk->SetBusy();
						break;
					}
					else
					{
						cout << "Invalid action for this clerk. Please choose again." << endl;
					}
				}
			}
		}

		if (!clerk->IsAvailable())
		{
			clerk->SetAvailable();
		}
	}
}

MailActions MailCustomerCommunication::MakingAction(const MailClerk& clerk) const
{
	char input = '0';

	cout << "Choose an action:" << endl;

	if (clerk.CanHandleAction(MailActions::RecivePackage))
		cout << "1. Receive a package" << endl;

	if (clerk.CanHandleAction(MailActions::DeliverPackage))
		cout << "2. Deliver a package" << endl;

	if (clerk.CanHandleAction(MailActions::MakePayment))
		cout << "3. Make a payment" << endl;

	if (clerk.CanHandleAction(MailActions::PurchaseProduct))
		cout << "4. Purchase a product" << endl;

	cout << "cancael your turn by pressing 5" << endl;

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
		if (clerk.CanHandleAction(action))
		{
			return action;
		}
	}
	return MailActions::None;
}