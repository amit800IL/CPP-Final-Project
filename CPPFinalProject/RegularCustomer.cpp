#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(string name, const DateOfBirth& dateOfBirth, MailActions choosedAction, const shared_ptr<MailClerk>& assignedClerk)
	: Customer(name, dateOfBirth, choosedAction, assignedClerk) {}

RegularCustomer::RegularCustomer(RegularCustomer&& customer) noexcept : Customer(move(customer)) {}
 