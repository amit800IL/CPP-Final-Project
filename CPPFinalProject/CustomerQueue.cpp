#include "CustomerQueue.h"

bool CustomerQueue::IsEmpty() const
{
	return (head == nullptr);
}

void CustomerQueue::Enqueue(Customer&& customer)
{
	unique_ptr<Node> newNode = make_unique<Node>(customer);

	if (IsEmpty() || newNode->customer.IsElderlyCustomer())
	{
		head = move(newNode);

		tail = head.get();
	}
	else if (IsEmpty())
	{
		unique_ptr<Node> current = move(head);

		while (current->next != nullptr && !newNode->customer.IsElderlyCustomer())
		{
			current = move(current->next);
		} 

		newNode->next = move(current->next);
		current->next = move(newNode);
	}

	cout << customer << " enqueued to the queue." << endl;
}

void CustomerQueue::Dequeue()
{
	if (IsEmpty())
	{
		return;
	}

	unique_ptr<Node> tempPointer = move(head);

	head = move(tempPointer->next);

	if (!head)
	{
		tail = nullptr;
	}

	cout << "Customer number: " << tempPointer->customer.GetCustomerNumber() << " dequeued from the queue.\n";
}

const Node& CustomerQueue::GetHead() const
{
	if (head)
	{
		return *head.get();
	}
	else
	{
		throw out_of_range("Queue is empty");
	}
}

