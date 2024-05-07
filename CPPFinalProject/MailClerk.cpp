
#include "MailClerk.h"
MailClerk::MailClerk(int id, const vector<MailActions>& actions)
	: clerkID(id), clerkActions(actions.begin(), actions.end())
{
	availableActions = clerkActions;
}
MailClerk::MailClerk(MailClerk&& mailOfficial) noexcept {}

bool MailClerk::CanHandleAction(MailActions action) const
{
	return find(availableActions.begin(), availableActions.end(), action) != availableActions.end();
}

void MailClerk::PerformAction(MailActions action)
{
	if (CanHandleAction(action))
	{
		switch (action)
		{
		case MailActions::ReceivePackage:
			cout << "Action " << static_cast<int>(MailActions::ReceivePackage) << endl;
			break;
		case MailActions::DeliverPackage:
			cout << "Action " << static_cast<int>(MailActions::DeliverPackage) << endl;
			break;
		case MailActions::MakePayment:
			cout << "Action " << static_cast<int>(MailActions::MakePayment) << endl;
			break;
		case MailActions::PurchaseProduct:
			cout << "Action " << static_cast<int>(MailActions::PurchaseProduct) << endl;
			break;
		default:
			cout << "Invalid action" << endl;
			break;
		}

		vector<MailActions>::iterator it = find(availableActions.begin(), availableActions.end(), action);

		if (it != availableActions.end())
		{
			availableActions.erase(it);
		}

		if (availableActions.empty())
		{
			availableActions = clerkActions;
		}
	}
}

bool MailClerk::IsAvailable()
{
	return !availableActions.empty();
}

void MailClerk::Print(ostream& os) const
{
	os << "Clerk number " << clerkID << " Is at your service " << endl;
}

int MailClerk::GivePriorityBasedOnAction(MailActions& action)
{
	int Bonus = 0;

	switch (action)
	{
	case MailActions::ReceivePackage:
		return Bonus += 40;
		break;
	case MailActions::DeliverPackage:
		return Bonus += 30;
		break;
	case MailActions::MakePayment:
		return Bonus += 20;
		break;
	case MailActions::PurchaseProduct:
		return Bonus += 10;
		break;
	default:
		break;
	}
}

vector<MailActions> MailClerk::GetClerkActions()
{
	return clerkActions;
}
