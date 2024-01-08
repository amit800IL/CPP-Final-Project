#include "Customer.h"

int Customer::lastAssignedCustomerNumber = 0;

Customer::Customer(DateOfBirth&& dateOfBirth)
{
	this->dateOfBirth = std::make_unique<DateOfBirth>(std::move(dateOfBirth));

	customerNumber = ++lastAssignedCustomerNumber;

	GetCustomerType();
}


Customer::Customer(Customer&& customer) noexcept :
	dateOfBirth{ std::move(customer.dateOfBirth) } {}

int Customer::GetCustomerNumber()
{
	return customerNumber;
}

bool Customer::GetCustomerType() const
{
	int age = dateOfBirth->CalcualteAge();

	if (age < 65)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	os << *customer.dateOfBirth << " , Age is: ";

	std::cout << customer.dateOfBirth->CalcualteAge() << std::endl;

	if (customer.GetCustomerType())
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

int DateOfBirth::CalcualteAge() const
{
	int yearClacultion = (*year - 1970) * 365 * 24;
	int monthCalcultion = (*month - 1) * 30 * 24;
	int dayCalculation = (*day - 1) * 24;

	auto now = std::chrono::system_clock::now();

	auto birth = std::chrono::system_clock::from_time_t(0) + std::chrono::hours(yearClacultion + monthCalcultion + dayCalculation);

	auto ageInSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - birth).count();

	return static_cast<int>(ageInSeconds / (24 * 60 * 60 * 365.25));
}

