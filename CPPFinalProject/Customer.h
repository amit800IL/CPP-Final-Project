#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "IPrintable.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>

using namespace std;

class MailClerk;

enum class MailActions
{
	Cancel,
	ReceivePackage,
	DeliverPackage,
	MakePayment,
	PurchaseProduct
};

struct DateOfBirth : public IPrintable
{

private:

	int day;
	int month;
	int year;

public:

	DateOfBirth(int day, int month, int year) : day(day), month(month), year(year) {}

	DateOfBirth(const DateOfBirth& other)
		:day(other.day),
		month(other.month),
		year(other.year)
	{};


	int GetDay()
	{
		return day;
	}

	int GetMonth()
	{
		return month;
	}

	int GetYear()
	{
		return year;
	}

	int CalcualteAge() const
	{
		int yearClacultion = (year - 1970) * 365 * 24;
		int monthCalcultion = (month - 1) * 30 * 24;
		int dayCalculation = (day - 1) * 24;

		chrono::system_clock::time_point now = chrono::system_clock::now();

		chrono::system_clock::time_point birth = chrono::system_clock::from_time_t(0) + chrono::hours(yearClacultion + monthCalcultion + dayCalculation);

		long long ageInSeconds = chrono::duration_cast<chrono::seconds>(now - birth).count();

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
	shared_ptr<MailClerk> assignedClerk;
	int customerNumber = 0;
	MailActions choosedAction;
	static int lastAssignedCustomerNumber;
	int uniqueId = 0;

public:

	Customer(const DateOfBirth& dateOfBirth, MailActions preferredAction, const shared_ptr<MailClerk>& assignedClerk);

	Customer(Customer&& customer) noexcept;

	int GetCustomerNumber() const;

	virtual int CustomerAge() const;

	virtual MailActions GetCustomerAction() const;

	int GenerateCustomerNumber();

	int GetCustomerID();

	virtual const shared_ptr<MailClerk>& GetAssignedClerk() const;

	void Print(ostream& os) const override;

	virtual ~Customer() override = default;
};
#endif

