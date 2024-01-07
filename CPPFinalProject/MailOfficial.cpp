#include "MailOfficial.h"

MailOfficial::MailOfficial(std::unique_ptr<IServiceCustomerMediator> mediator) : mediator(std::move(mediator)) {}

MailOfficial::MailOfficial(MailOfficial&& mailOfficial) noexcept : mediator(std::move(mailOfficial.mediator)) {}

const std::unique_ptr<IServiceCustomerMediator>& MailOfficial::getMediator()
{
	return mediator;
}