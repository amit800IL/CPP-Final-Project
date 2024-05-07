#pragma once

#include "Customer.h"
#include "MailCustomerCommunication.h"
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector> 
#include <algorithm> 

using namespace std;

class MailClerk : public IPrintable
{
private:
	int clerkID;
	vector<MailActions> availableActions;
	vector<MailActions> clerkActions;
public:
	MailClerk(int id, const vector<MailActions>& actions);

	MailClerk(MailClerk&& mailOfficial) noexcept;

	bool CanHandleAction(MailActions action) const;

	void PerformAction(MailActions action);

	bool IsAvailable();

	vector<MailActions> GetClerkActions();

	void Print(ostream& os) const override;

	int GivePriorityBasedOnAction(MailActions& action);

	~MailClerk() override = default;
};

