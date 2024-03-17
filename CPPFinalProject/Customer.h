#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <chrono>
#include <iostream>
#include <memory>

using namespace std;


struct DateOfBirth
{
	std::unique_ptr<int> day;
	std::unique_ptr<int> month;
	std::unique_ptr<int> year;

	DateOfBirth(int day, int month, int year) : day(std::make_unique<int>(day)), month(std::make_unique<int>(month)), year(std::make_unique<int>(year)) {}

	DateOfBirth(const DateOfBirth& other) 
		:day(std::make_unique<int>(*other.day)),
		month(std::make_unique<int>(*other.month)),
		year(std::make_unique<int>(*other.year))
	{};

	friend std::ostream& operator<<(std::ostream& os, const DateOfBirth& date);

	int CalcualteAge() const;
};

class Customer
{
	friend std::ostream& operator<<(std::ostream& os, const Customer& customer);

protected:
	std::unique_ptr<DateOfBirth> dateOfBirth;
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

