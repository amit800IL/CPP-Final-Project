#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <chrono>
#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>

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

	int CalcualteAge() const
	{
		int yearClacultion = (*year - 1970) * 365 * 24;
		int monthCalcultion = (*month - 1) * 30 * 24;
		int dayCalculation = (*day - 1) * 24;

		auto now = chrono::system_clock::now();

		auto birth = chrono::system_clock::from_time_t(0) + chrono::hours(yearClacultion + monthCalcultion + dayCalculation);

		auto ageInSeconds = chrono::duration_cast<chrono::seconds>(now - birth).count();

		return static_cast<int>(ageInSeconds / (24 * 60 * 60 * 365.25));
	}
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

	int GetCustomerNumber() const;

	virtual int CustomerAge() const;

	//string SerializeCustomer(const unique_ptr<Customer>& customer) const;

	//std::string SerializeCustomer() const;

	//Customer DeserializeCustomer(const std::string& data);

	virtual ~Customer() = default;
};
#endif

