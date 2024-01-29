#include "CustomerQueue.h"

bool CustomerQueue::IsEmpty() const
{
	return (head == nullptr);
}

void CustomerQueue::Enqueue(Customer&& customer)
{
	std::unique_ptr<Node> newNode = std::make_unique<Node>(customer);

	if (IsEmpty() || newNode->customer.IsElderlyCustomer())
	{
		head = std::move(newNode);

		tail = head.get();
	}
	else if (IsEmpty())
	{
		std::unique_ptr<Node> current = std::move(head);

		while (current->next != nullptr && !newNode->customer.IsElderlyCustomer())
		{
			current = std::move(current->next);
		} 

		newNode->next = std::move(current->next);
		current->next = std::move(newNode);
	}

	std::cout << customer << " enqueued to the queue." << std::endl;
}

void CustomerQueue::Dequeue()
{
	if (IsEmpty())
	{
		return;
	}

	std::unique_ptr<Node> tempPointer = std::move(head);

	head = std::move(tempPointer->next);

	if (!head)
	{
		tail = nullptr;
	}

	std::cout << "Customer number: " << tempPointer->customer.GetCustomerNumber() << " dequeued from the queue.\n";
}

const Node& CustomerQueue::GetHead() const
{
	if (head)
	{
		return *head.get();
	}
	else
	{
		throw std::out_of_range("Queue is empty");
	}
}

