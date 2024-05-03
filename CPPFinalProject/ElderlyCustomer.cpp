#include "ElderlyCustomer.h"

ElderlyCustomer::ElderlyCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction)
	: Customer(dateOfBirth, choosedAction) {}

ElderlyCustomer::ElderlyCustomer(ElderlyCustomer&& customer) noexcept : Customer(move(customer)) {}
