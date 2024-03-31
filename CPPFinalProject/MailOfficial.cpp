#include "MailOfficial.h"

MailOfficial::MailOfficial() {}

MailOfficial::MailOfficial(MailOfficial&& mailOfficial) noexcept {}

void MailOfficial::PerformAction(MailActions action)
{
	switch (action)
	{
	case MailActions::RecivePackage:
		cout << "Here is your Package" << endl;
		break;
	case MailActions::DeliverPackage:
		cout << "Here is your Package" << endl;
		break;
	case MailActions::MakePayment:
		cout << "Here is your Package" << endl;
		break;
	case MailActions::PurchaseProduct:
		cout << "Here is your Package" << endl;
		break;
	default:
		std::cout << "Invalid action" << std::endl;
		break;
	}
}
