#pragma once

#include "Customer.h"
#include "MailCustomerCommunication.h"
#include <iostream>
#include <memory>
#include <unordered_set>

using namespace std;

enum class MailActions
{
	None,
	RecivePackage,
	DeliverPackage,
	MakePayment,
	PurchaseProduct,
};

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

	void Print(ostream& os) const override;

	//void SetAvailable();

	//void SetBusy(MailActions action); // Update handledActions when busy

	//void ClearHandledAction(MailActions action); // Clear a handled action

	~MailClerk() override = default;
};

