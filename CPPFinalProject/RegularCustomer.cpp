#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(const DateOfBirth& dateOfBirth)
	: Customer(dateOfBirth) {}

RegularCustomer::RegularCustomer(RegularCustomer&& customer) noexcept : Customer(std::move(customer)) {}