#ifndef CUSTOMERQUEUEITERATOR_H
#define CUSTOMERQUEUEITERATOR_H

#include "CustomerQueue.h"

struct Node;

class CustomerQueueIterator
{

private:
	Node* current;

public:
	CustomerQueueIterator(Node* node);
	CustomerQueueIterator& operator++();
	bool operator!=(const CustomerQueueIterator& other) const;
	Customer& operator*() const;
};

#endif