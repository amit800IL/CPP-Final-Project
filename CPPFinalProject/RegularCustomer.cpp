#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction)
	: Customer(dateOfBirth, choosedAction) {}

RegularCustomer::RegularCustomer(RegularCustomer&& customer) noexcept : Customer(move(customer)) {}
