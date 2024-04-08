#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(const DateOfBirth& dateOfBirth)
	: Customer(dateOfBirth) {}

RegularCustomer::RegularCustomer(RegularCustomer&& customer) noexcept : Customer(move(customer)) {}

int RegularCustomer::CustomerAge() const
{
	return Customer::CustomerAge();
}
