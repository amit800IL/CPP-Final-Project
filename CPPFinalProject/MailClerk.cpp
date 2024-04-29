
#include "MailClerk.h"
MailClerk::MailClerk(int id, const vector<MailActions>& actions)
	: clerkID(id), actionSequence(actions.begin(), actions.end()) {
	// Initially, all actions are available
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

		availableActions.erase(action);

		// If no available actions left, reset available actions
		if (availableActions.empty()) {
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

//void MailClerk::SetAvailable()
//{
//	
//}
//
//void MailClerk::SetBusy(MailActions action)
//{
//	handledActions.insert(action);
//	isClerkBusy = true;
//}
//
//void MailClerk::ClearHandledAction(MailActions action)
//{
//	handledActions.erase(action);
//
//	if (handledActions.empty())
//	{
//		isClerkBusy = false;
//	}

