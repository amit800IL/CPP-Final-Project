#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <memory>

struct DateOfBirth
{
	std::unique_ptr<int> day;
	std::unique_ptr<int> month;
	std::unique_ptr<int> year;

	DateOfBirth(int day, int month, int year) : day(std::make_unique<int>(day)), month(std::make_unique<int>(month)), year(std::make_unique<int>(year)) {}

	DateOfBirth(DateOfBirth&& dateOfBirth) noexcept : day(std::move(dateOfBirth.day)), month(std::move(dateOfBirth.month)), year(std::move(dateOfBirth.year)) {}

	friend std::ostream& operator<<(std::ostream& os, const DateOfBirth& date);
};

class Customer
{
	friend std::ostream& operator<<(std::ostream& os, const Customer& customer);

private:
	std::unique_ptr<bool> isRegularCustomer;
	std::unique_ptr<DateOfBirth> dateOfBirth;
	int customerNumber; 

	static int lastAssignedCustomerNumber;

public:

	Customer(bool isRegularCustomer, DateOfBirth&& dateOfBirth);

	Customer(Customer&& customer) noexcept;

	int GetCustomerNumber();

	~Customer();
};
#endif

