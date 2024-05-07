#include "ElderlyCustomer.h"

ElderlyCustomer::ElderlyCustomer(string name, const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk)
	: Customer(name, dateOfBirth, choosedAction, assignedClerk) {}

ElderlyCustomer::ElderlyCustomer(ElderlyCustomer&& customer) noexcept : Customer(move(customer)) {}
