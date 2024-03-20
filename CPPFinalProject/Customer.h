#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <chrono>
#include <iostream>
#include <memory>

using namespace std;


struct DateOfBirth
{
	unique_ptr<int> day;
	unique_ptr<int> month;
	unique_ptr<int> year;

	DateOfBirth(int day, int month, int year) : day(make_unique<int>(day)), month(make_unique<int>(month)), year(make_unique<int>(year)) {}

	DateOfBirth(const DateOfBirth& other) 
		:day(make_unique<int>(*other.day)),
		month(make_unique<int>(*other.month)),
		year(make_unique<int>(*other.year))
	{};

	friend std::ostream& operator<<(ostream& os, const DateOfBirth& date);

	int CalcualteAge() const;
};

class Customer
{
	friend ostream& operator<<(ostream& os, const Customer& customer);

protected:
	unique_ptr<DateOfBirth> dateOfBirth;
	int customerNumber;

	static int lastAssignedCustomerNumber;

public:

	Customer(const DateOfBirth& dateOfBirth);

	Customer(Customer&& customer) noexcept;

	int GetCustomerNumber();

	bool IsElderlyCustomer() const;

	~Customer();
};
#endif

