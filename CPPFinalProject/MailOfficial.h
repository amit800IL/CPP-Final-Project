#pragma once

#include "Customer.h"
#include "IServiceCustomerMediator.h"
#include "MailActions.h"
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

class MailClerk
{
private:
	int clerkID;
	std::unordered_set<MailActions> availableActions;
public:
	MailClerk(int id, const unordered_set<MailActions>& actions);

	MailClerk(MailClerk&& mailOfficial) noexcept;

	bool canHandleAction(MailActions action) const;

	void PerformAction(MailActions action);
};

