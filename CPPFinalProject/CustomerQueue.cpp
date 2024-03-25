#include "CustomerQueue.h"

bool CustomerQueue::IsEmpty() const
{
	return (head == nullptr);
}

void CustomerQueue::Enqueue(Customer&& customer) {
    unique_ptr<Node> newNode = make_unique<Node>(customer);

    if (IsEmpty()) {
        head = move(newNode);
        tail = head.get();
    }
    else
    {
        tail->next = move(newNode);
        tail = tail->next.get();
    }

    cout << customer << " enqueued to the queue." << endl;
}

unique_ptr<Node> CustomerQueue::Dequeue()
{
    if (IsEmpty())
    {
        throw out_of_range("Queue is empty");
    }

    unique_ptr<Node> tempPointer = move(head);
    head = move(tempPointer->next);

    if (!head)
    {
        tail = nullptr;
    }

    cout << "Customer number: " << tempPointer->customer.GetCustomerNumber() << " dequeued from the queue." << endl;

    return tempPointer;
}

const Node& CustomerQueue::GetHead() const {
    if (IsEmpty()) {
        throw out_of_range("Queue is empty");
    }
    else {
        return *head.get();
    }
}

CustomerQueueIterator CustomerQueue::begin() const {
    return CustomerQueueIterator(head.get());
}

CustomerQueueIterator CustomerQueue::end() const {
    return CustomerQueueIterator(nullptr);
}
