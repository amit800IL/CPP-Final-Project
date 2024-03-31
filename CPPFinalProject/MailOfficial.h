#pragma once

#include "Customer.h"
#include "IServiceCustomerMediator.h"
#include "MailActions.h"
#include <iostream>
#include <memory>

using namespace std;

enum class MailActions {
	RecivePackage,
	DeliverPackage,
	MakePayment,
	PurchaseProduct,
};

class MailOfficial
{

public:
	MailOfficial();
	MailOfficial(MailOfficial&& mailOfficial) noexcept;

	void PerformAction(MailActions action);
};

