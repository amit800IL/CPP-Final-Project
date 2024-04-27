#include "Customer.h"

int Customer::lastAssignedCustomerNumber = 0;

Customer::Customer(const DateOfBirth& dateOfBirth)
{
	this->dateOfBirth = make_unique<DateOfBirth>(dateOfBirth);

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

ostream& operator<<(ostream& os, const DateOfBirth& date)
{
	os << "Date of Birth: " << *date.day << '/' << *date.month << '/' << *date.year;
	return os;
}

ostream& operator<<(ostream& os, const Customer& customer)
{
	os << *customer.dateOfBirth << " , Age is: " << customer.CustomerAge() << ", Customer Number : " << customer.customerNumber;

	return os;
}

//std::string Customer::SerializeCustomer() const 
//{
//	std::stringstream ss;
//	ss << *this << ',' << endl;
//	return ss.str();
//}
//
//Customer Customer::DeserializeCustomer(const std::string& data) 
//{
//	std::stringstream ss(data);
//	int customerNumber, day, month, year;
//	char comma;
//	ss >> customerNumber >> comma >> day >> comma >> month >> comma >> year;
//	DateOfBirth dob(day, month, year);
//	return Customer(dob); // Assuming Customer constructor takes DateOfBirth
//}



