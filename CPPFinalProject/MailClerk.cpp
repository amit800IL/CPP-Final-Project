
#include "MailClerk.h"

MailClerk::MailClerk(int id, const unordered_set<MailActions>& actions) : clerkID{ id }, availableActions{ actions } {}

MailClerk::MailClerk(MailClerk&& mailOfficial) noexcept {}

bool MailClerk::CanHandleAction(MailActions action) const
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

bool MailClerk::IsAvailable()
{
	if (!isClerkBusy) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MailClerk::SetAvailable()
{
	isClerkBusy = false;
}

void MailClerk::SetBusy()
{
	isClerkBusy = true;
}

std::ostream& operator<<(ostream& os, const MailClerk& date)
{
	cout << "Clerk number " << date.clerkID << " Is at your service " << endl;

	return os;
}