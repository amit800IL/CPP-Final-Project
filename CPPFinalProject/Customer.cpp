#include "Customer.h"

int Customer::lastAssignedCustomerNumber = 0;

Customer::Customer(bool isRegularCustomer, DateOfBirth&& dateOfBirth)
{
	this->isRegularCustomer = std::make_unique<bool>(isRegularCustomer);
	this->dateOfBirth = std::make_unique<DateOfBirth>(std::move(dateOfBirth));
	
	customerNumber = ++lastAssignedCustomerNumber;

	std::cout << customerNumber << std::endl;
}

Customer::Customer(Customer&& customer) noexcept :
isRegularCustomer{std::move(customer.isRegularCustomer)}, 
dateOfBirth{std::move(customer.dateOfBirth)} {}

int Customer::GetCustomerNumber()
{
	return customerNumber;
}

Customer::~Customer() {}

std::ostream& operator<<(std::ostream& os, const DateOfBirth& date)
{
	os << "Date of Birth: " << *date.day << '/' << *date.month << '/' << *date.year;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Customer& customer)
{
	os << "Customer Details:" << std::endl;
	os << "Customer date of birth: " << *customer.dateOfBirth << std::endl;
	if (*customer.isRegularCustomer)
	{
		os << "Customer Type: " << "RegualrCustomer" << std::endl;
	}
	else
	{
		os << "Customer Type: " << "Elderly Customer" << std::endl;
	}

	os << "Customer Number: " << customer.customerNumber;

	return os;
}