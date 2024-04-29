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
	std::unordered_set<MailActions> availableActions;
	bool isClerkBusy = false;
public:
	MailClerk(int id, const unordered_set<MailActions>& actions);

	MailClerk(MailClerk&& mailOfficial) noexcept;

	bool CanHandleAction(MailActions action) const;

	void PerformAction(MailActions action);

	bool IsAvailable();

	void Print(ostream& os) const override;

	void SetAvailable();
	void SetBusy();

	~MailClerk() override = default;
};

