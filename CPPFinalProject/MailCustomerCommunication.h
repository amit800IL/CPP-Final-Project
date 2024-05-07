
#ifndef MAILCUSTOMERCOMMUNICATION_H
#define MAILCUSTOMERCOMMUNICATION_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <memory>
#include "Customer.h"
#include "MailClerk.h"
#include "Customer.h"
#include "ElderlyCustomer.h"
#include "RegularCustomer.h"
#include <chrono>
#include <ctime>   
#include <thread>  
#include <iomanip>

using namespace std;

enum class MailActions;
class MailClerk;

class MailCustomerCommunication
{

private:
	vector<shared_ptr<MailClerk>> clerks;
	chrono::time_point<chrono::system_clock> timeServed;
	chrono::duration<double> waitingTime;
public:
	MailCustomerCommunication(const vector<shared_ptr<MailClerk>>& clerks);
	shared_ptr<MailClerk> FindAvailableClerk(const MailActions& action) const;
	unique_ptr<Customer> CreateCustomer();
	vector<shared_ptr<MailClerk>> GetClerksList();
	void CallCustomer(const Customer& customer);
	MailActions ChooseAction();

	void CalculateServiceDuration();

	~MailCustomerCommunication() = default;
};


#endif