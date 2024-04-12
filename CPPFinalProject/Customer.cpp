#include "Customer.h"

int Customer::lastAssignedCustomerNumber = 0;

Customer::Customer(const DateOfBirth& dateOfBirth)
{
	this->dateOfBirth = make_unique<DateOfBirth>(dateOfBirth);

	customerNumber = ++lastAssignedCustomerNumber;

	CustomerAge();
}

Customer::Customer(Customer&& customer) noexcept : dateOfBirth(move(customer.dateOfBirth)) {}


int Customer::GetCustomerNumber()
{
	return customerNumber;
}

int Customer::CustomerAge() const
{
	return dateOfBirth->CalcualteAge();
}

ostream& operator<<(ostream& os, const DateOfBirth& date)
{
	os << "Date of Birth: " << *date.day << '/' << *date.month << '/' << *date.year;
	return os;
}

ostream& operator<<(ostream& os, const Customer& customer)
{
	os << "Customer Details:" << endl;
	os << *customer.dateOfBirth << " , Age is: ";

	cout << customer.dateOfBirth->CalcualteAge() << endl;

	if (customer.CustomerAge() >= 65)
	{
		os << "Customer Type: " << "Elderly Customer" << endl;
	}
	else
	{
		os << "Customer Type: " << "Regular Customer" << endl;
	}


	os << "Customer Number: " << customer.customerNumber;

	return os;
}


