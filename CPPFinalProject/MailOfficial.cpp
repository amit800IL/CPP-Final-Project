#include "MailOfficial.h"

MailClerk::MailClerk(int id, const unordered_set<MailActions>& actions) : clerkID{ id }, availableActions{ actions }
{
	cout << "Clerk id: " << id << "At your service" << endl;
}

MailClerk::MailClerk(MailClerk&& mailOfficial) noexcept {}

bool MailClerk::canHandleAction(MailActions action) const
{
	return availableActions.count(action) > 0;
}

void MailClerk::PerformAction(MailActions action)
{
	switch (action)
	{
	case MailActions::RecivePackage:
		cout << "Here is your Package" << endl;
		break;
	case MailActions::DeliverPackage:
		cout << "Package has been delivered" << endl;
		break;
	case MailActions::MakePayment:
		cout << "Payment made succesfully" << endl;
		break;
	case MailActions::PurchaseProduct:
		cout << "Product has been purchased" << endl;
		break;
	default:
		std::cout << "Invalid action" << std::endl;
		break;
	}
}
