#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk)
	: Customer(dateOfBirth, choosedAction, assignedClerk) {}

RegularCustomer::RegularCustomer(RegularCustomer&& customer) noexcept : Customer(move(customer)) {}
 