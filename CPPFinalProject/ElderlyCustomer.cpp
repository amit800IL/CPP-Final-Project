#include "ElderlyCustomer.h"

ElderlyCustomer::ElderlyCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction)
	: Customer(dateOfBirth, choosedAction) {}

ElderlyCustomer::ElderlyCustomer(ElderlyCustomer&& customer) noexcept : Customer(move(customer)) {}

int ElderlyCustomer::GenerateCustomerNumber()
{
	Customer::GenerateCustomerNumber();

	int actionPriority = static_cast<int>(choosedAction);
	int agePriority = CustomerAge();

	switch (choosedAction)
	{
	case MailActions::ReceivePackage:
		priorityScore = (actionPriority * 10) + agePriority;
		break;
	case MailActions::DeliverPackage:
		priorityScore = (actionPriority * 5) + agePriority;
		break;
	case MailActions::MakePayment:
		priorityScore = (actionPriority * 3) + agePriority;
		break;
	case MailActions::PurchaseProduct:
		priorityScore = (actionPriority * 2) + agePriority;
		break;
	default:
		break;
	}

	return priorityScore;
}