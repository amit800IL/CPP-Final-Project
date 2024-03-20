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
		tail = move(head);

		head = move(newNode);
	}
	else if (IsEmpty())
	{
		unique_ptr<Node> current = move(tail);

		while (current->next != nullptr && !newNode->customer.IsElderlyCustomer())
		{
			current = move(current->next);
		} 

		newNode->next = move(current->next);
		current->next = move(newNode);
	}

	cout << customer << " enqueued to the queue." << endl;
}

unique_ptr<Node> CustomerQueue::Dequeue()
{
	unique_ptr<Node> tempPointer = move(tail);

	tail = move(tempPointer->next);

	//if (!head)
	//{
	//	tail = nullptr;
	//}

	cout << "Customer number: " << tempPointer->customer.GetCustomerNumber() << " dequeued from the queue." << endl;

	return tempPointer;
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

