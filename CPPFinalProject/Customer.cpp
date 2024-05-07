#include "Customer.h"

Customer::Customer(string name, const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk)
{
	this->name = name;

	this->dateOfBirth = make_unique<DateOfBirth>(dateOfBirth);

	this->choosedAction = choosedAction;

	this->assignedClerk = assignedClerk;

	GenerateCustomerNumber();
}

Customer::Customer(Customer&& customer) noexcept : name(customer.name), dateOfBirth(move(customer.dateOfBirth)), choosedAction(customer.choosedAction), assignedClerk(move(customer.assignedClerk)) {}


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
	//Gets the birth date of the customer

	int birthDay = dateOfBirth->GetDay();
	int birthMonth = dateOfBirth->GetMonth();
	int birthYear = dateOfBirth->GetYear();

	//Calcultes the id based on the birth date values

	uniqueId = (birthYear * 10000) + (birthMonth * 100) + birthDay;

	//Divides by 10 so value will not be too big

	uniqueId = uniqueId / 10;

	//After that, it adds more to the uniqeid value based on the chosen action

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

	//Returns the uniqe id, the uniqe id purpose is to distinct customer from customer
	//UniqeId is not part of the queue system, this number exists only so each customer has ID

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
	cout << "Customer name: " << name << ", " ; dateOfBirth->Print(os), os << " , Age: " << CustomerAge() << ", Customer Number: " << uniqueId << endl;
}

MailActions Customer::GetCustomerAction() const
{
	return choosedAction;
}




