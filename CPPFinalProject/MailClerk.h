#pragma once

#include "Customer.h"
#include "MailCustomerCommunication.h"
#include <iostream>
#include <memory>
#include <unordered_set>

using namespace std;

class MailClerk : public IPrintable
{
private:
	int clerkID;
	unordered_set<MailActions> availableActions;
	vector<MailActions> actionSequence;
	bool isClerkBusy = false;
public:
	MailClerk(int id, const vector<MailActions>& actions);

	MailClerk(MailClerk&& mailOfficial) noexcept;

	bool CanHandleAction(MailActions action) const;

	void PerformAction(MailActions action);

	bool IsAvailable();

	MailActions GetClerkAction(MailActions& action);

	vector<MailActions> GetActionSequence();

	void Print(ostream& os) const override;

	~MailClerk() override = default;
};

