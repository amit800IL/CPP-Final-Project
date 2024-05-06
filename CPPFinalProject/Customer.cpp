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

	int birthDay = dateOfBirth->GetDay();
	int birthMonth = dateOfBirth->GetMonth();
	int birthYear = dateOfBirth->GetYear();

	uniqueId = (birthYear * 10000) + (birthMonth * 100) + birthDay;

	uniqueId = uniqueId / 10;

	switch (choosedAction)
	{
	case MailActions::ReceivePackage:
		uniqueId += 100;
		break;
	case MailActions::DeliverPackage:
		uniqueId += 200;
		break;
	case MailActions::MakePayment:
		uniqueId += 300;
		break;
	case MailActions::PurchaseProduct:
		uniqueId += 400;
		break;
	default:
		break;
	}

	return uniqueId;
}

int Customer::GetCustomerID()
{
	return uniqueId;
}

const shared_ptr<MailClerk>& Customer::GetAssignedClerk() const
{
	return assignedClerk;
}

void Customer::Print(ostream& os) const
{
	dateOfBirth->Print(os), os << " , Age is: " << CustomerAge() << ", Customer Number : " << uniqueId << endl;
}

MailActions Customer::GetCustomerAction() const
{
	return choosedAction;
}





