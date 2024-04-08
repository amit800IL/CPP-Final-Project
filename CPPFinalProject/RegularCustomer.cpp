#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(const DateOfBirth& dateOfBirth)
	: Customer(dateOfBirth) 
{
	cout << "Regular Customer, age: " << this->CustomerAge() << endl;
}

RegularCustomer::RegularCustomer(RegularCustomer&& customer) noexcept : Customer(move(customer)) {}

int RegularCustomer::CustomerAge() const
{
	return Customer::CustomerAge();
}
