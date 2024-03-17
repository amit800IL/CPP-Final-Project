#include "ElderlyCustomer.h"

ElderlyCustomer::ElderlyCustomer(const DateOfBirth& dateOfBirth) 
	: Customer(dateOfBirth) {}

ElderlyCustomer::ElderlyCustomer(ElderlyCustomer&& customer) noexcept : Customer(move(customer)) {}