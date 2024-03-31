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
