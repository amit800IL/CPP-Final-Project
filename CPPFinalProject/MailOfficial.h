#pragma once

#include <iostream>
#include <memory>
#include "MailActions.h"
#include "Customer.h"
#include "IServiceCustomerMediator.h"

class MailOfficial
{
private:
	std::unique_ptr<IServiceCustomerMediator> mediator;
public:
	MailOfficial(std::unique_ptr<IServiceCustomerMediator> mediator);
	MailOfficial(MailOfficial&& mailOfficial) noexcept;
	const std::unique_ptr<IServiceCustomerMediator>& getMediator();
};

