#include "Customer.h"

int Customer::lastAssignedCustomerNumber = 0;

Customer::Customer(const DateOfBirth& dateOfBirth, MailActions choosedAction)
{
	this->dateOfBirth = make_unique<DateOfBirth>(dateOfBirth);

	this->choosedAction = choosedAction;

	GenerateCustomerNumber();
}

Customer::Customer(Customer&& customer) noexcept : dateOfBirth(move(customer.dateOfBirth)) {}


int Customer::GetCustomerNumber() const
{
	return customerNumber;
}

int Customer::CustomerAge() const
{
	return dateOfBirth->CalcualteAge();
}

int Customer::GenerateCustomerNumber()
{
	int actionPriority = static_cast<int>(choosedAction);

	switch (choosedAction)
	{
	case MailActions::ReceivePackage:
		priorityScore = (actionPriority * 10);
		break;
	case MailActions::DeliverPackage:
		priorityScore = (actionPriority * 5);
		break;
	case MailActions::MakePayment:
		priorityScore = (actionPriority * 3);
		break;
	case MailActions::PurchaseProduct:
		priorityScore = (actionPriority * 2);
		break;
	default:
		break;
	}

	return priorityScore;
}

int Customer::GetPriorityScore()
{
	return priorityScore;
}

void Customer::Print(ostream& os) const
{
	dateOfBirth->Print(os), os << " , Age is: " << CustomerAge() << ", Customer Number : " << priorityScore << "A" << endl;
}

MailActions Customer::GetCustomerAction() const
{
	return choosedAction;
}





