#include "Customer.h"

int Customer::lastAssignedCustomerNumber = 0;

Customer::Customer(const DateOfBirth& dateOfBirth, MailActions choosedAction)
{
	this->dateOfBirth = make_unique<DateOfBirth>(dateOfBirth);

	this->choosedAction = choosedAction;

	customerNumber = ++lastAssignedCustomerNumber;
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

void Customer::Print(ostream& os) const
{
   dateOfBirth->Print(os) , os << " , Age is: " << CustomerAge() << ", Customer Number : " << customerNumber << endl;
}

MailActions Customer::GetCustomerAction() const
{
	return choosedAction;
}



