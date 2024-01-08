#pragma once

#include <iostream>
#include <memory>
#include "MailActions.h"
#include "Customer.h"
#include "IServiceCustomerMediator.h"

class MailOfficial
{
public:
	MailOfficial();
	MailOfficial(MailOfficial&& mailOfficial) noexcept;
};

