#include "ElderlyCustomer.h"

ElderlyCustomer::ElderlyCustomer(const DateOfBirth& dateOfBirth) 
	: Customer(dateOfBirth)
{
	cout << "Eldelry Customer, age: " << this->CustomerAge() << endl;
}

ElderlyCustomer::ElderlyCustomer(ElderlyCustomer&& customer) noexcept : Customer(move(customer)) {}

int ElderlyCustomer::CustomerAge() const
{
	return Customer::CustomerAge();
}