#include "ElderlyCustomer.h"

ElderlyCustomer::ElderlyCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk)
	: Customer(dateOfBirth, choosedAction, assignedClerk) {}

ElderlyCustomer::ElderlyCustomer(ElderlyCustomer&& customer) noexcept : Customer(move(customer)) {}
