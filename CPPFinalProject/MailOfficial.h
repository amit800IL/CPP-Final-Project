#pragma once

#include <iostream>
#include <memory>
#include "MailActions.h"
#include "Customer.h"
#include "IServiceCustomerMediator.h"

class MailOfficial
{
private:
	std::shared_ptr<IServiceCustomerMediator> mediator;
public:
	MailOfficial(std::shared_ptr<IServiceCustomerMediator> mediator);
	MailOfficial(MailOfficial&& mailOfficial) noexcept;
};

