#include "CustomerQueueIterator.h"

CustomerQueueIterator::CustomerQueueIterator(Node* node) : current(node) {}

CustomerQueueIterator& CustomerQueueIterator::operator++() {
	if (current) {
		current = current->next.get();
	}
	return *this;
}

bool CustomerQueueIterator::operator!=(const CustomerQueueIterator& other) const {
	return current != other.current;
}

Customer& CustomerQueueIterator::operator*() const {
	return current->customer;
}