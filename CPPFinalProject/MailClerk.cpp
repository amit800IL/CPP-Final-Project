
#include "MailClerk.h"
MailClerk::MailClerk(int id, const vector<MailActions>& actions)
	: clerkID(id), actionSequence(actions.begin(), actions.end())
{
	availableActions.insert(actionSequence.begin(), actionSequence.end());
}
MailClerk::MailClerk(MailClerk&& mailOfficial) noexcept {}

bool MailClerk::CanHandleAction(MailActions action) const
{
	return availableActions.count(action) > 0;
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
			std::cout << "Invalid action" << std::endl;
			break;
		}

		availableActions.erase(action);

		if (availableActions.empty())
		{
			availableActions.insert(actionSequence.begin(), actionSequence.end());
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

MailActions MailClerk::GetClerkAction(MailActions& action)
{
	switch (action)
	{
	case MailActions::ReceivePackage:
		return actionSequence[0];
		break;
	case MailActions::DeliverPackage:
		return actionSequence[1];
		break;
	case MailActions::MakePayment:
		return actionSequence[2];
		break;
	case MailActions::PurchaseProduct:
		return actionSequence[3];
		break;
	default:
		break;
	}
}

vector<MailActions> MailClerk::GetActionSequence()
{
	return actionSequence;
}
