#include "Customer.h"

int Customer::lastAssignedCustomerNumber = 0;

Customer::Customer(const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk)
{
	this->dateOfBirth = make_unique<DateOfBirth>(dateOfBirth);

	this->choosedAction = choosedAction;

	this->assignedClerk = assignedClerk;

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

int Customer::GetPriorityScore()
{
	return priorityScore;
}

const shared_ptr<MailClerk>& Customer::GetAssignedClerk() const
{
	return assignedClerk;
}

void Customer::Print(ostream& os) const
{
	dateOfBirth->Print(os), os << " , Age is: " << CustomerAge() << ", Customer Number : " << priorityScore << endl;
}

MailActions Customer::GetCustomerAction() const
{
	return choosedAction;
}





