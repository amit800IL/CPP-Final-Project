#include "CustomerQueue.h"

bool CustomerQueue::IsEmpty() const
{
	return (head == nullptr);
}

void CustomerQueue::Enqueue(Customer customer)
{
	std::unique_ptr<Node> newNode = std::make_unique<Node>(customer);

	if (IsEmpty())
	{
		head = std::move(newNode);
		tail = head.get();
	}
	else
	{
		tail->next = std::move(newNode);
		tail = tail->next.get();
	}

	std::cout << "customer" << " enqueued to the queue.\n";
}

void CustomerQueue::Dequeue()
{
	if (IsEmpty())
	{
	   return;
	}

	auto temp = std::move(head);

	head = std::move(temp->next);

	if (!head)
	{
	   tail = nullptr;
	}

	std::cout << "Customer" << " dequeued from the queue.\n";
}
