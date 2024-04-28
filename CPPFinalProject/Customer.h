#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <chrono>
#include "IPrintable.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>

using namespace std;


struct DateOfBirth : public IPrintable
{
	int day;
	int month;
	int year;

	DateOfBirth(int day, int month, int year) : day(day), month(month), year(year) {}

	DateOfBirth(const DateOfBirth& other)
		:day(other.day),
		month(other.month),
		year(other.year)
	{};


	int CalcualteAge() const
	{
		int yearClacultion = (year - 1970) * 365 * 24;
		int monthCalcultion = (month - 1) * 30 * 24;
		int dayCalculation = (day - 1) * 24;

		auto now = chrono::system_clock::now();

		auto birth = chrono::system_clock::from_time_t(0) + chrono::hours(yearClacultion + monthCalcultion + dayCalculation);

		auto ageInSeconds = chrono::duration_cast<chrono::seconds>(now - birth).count();

		return static_cast<int>(ageInSeconds / (24 * 60 * 60 * 365.25));
	}

	void Print(ostream& os) const override
	{
		os << "Date of Birth: " << day << '/' << month << '/' << year;
	}
};

class Customer : public IPrintable
{

protected:
	unique_ptr<DateOfBirth> dateOfBirth;
	int customerNumber;

	static int lastAssignedCustomerNumber;

public:

	Customer(const DateOfBirth& dateOfBirth);

	Customer(Customer&& customer) noexcept;

	int GetCustomerNumber() const;

	virtual int CustomerAge() const;

	void Print(ostream& os) const override;

	bool operator<(const Customer& other) const {
		// Define the comparison logic based on customer priority (age)
		return CustomerAge() < other.CustomerAge();
	}

	virtual ~Customer() = default;
};
#endif

