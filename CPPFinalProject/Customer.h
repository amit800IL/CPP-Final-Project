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

	DateOfBirth(int day, int month, int year) : day(nullptr), month(nullptr), year(nullptr) {}
};

class Customer
{
private:
	std::unique_ptr<bool> isRegularCustomer;
	std::unique_ptr<DateOfBirth> dateOfBirth;
	std::unique_ptr<int> customerNumber;

	Customer(bool &isRegularCustomer, DateOfBirth &dateOfBirth);

	Customer(Customer&& customer) noexcept;
};
#endif // !CUSTOMER_H

