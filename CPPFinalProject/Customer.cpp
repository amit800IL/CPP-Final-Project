#include "Customer.h"

Customer::Customer(bool isRegularCustomer, DateOfBirth dateOfBirth)
{
	this->isRegularCustomer = std::make_unique<bool>(isRegularCustomer);
	this->dateOfBirth = std::make_unique<DateOfBirth>(std::move(dateOfBirth));
	
	customerNumber++;

	std::cout << customerNumber << std::endl;
}

Customer::Customer(Customer&& customer) noexcept :
isRegularCustomer{std::move(customer.isRegularCustomer)}, 
dateOfBirth{std::move(customer.dateOfBirth)} {}

Customer::~Customer() {}