#include "CustomerQueue.h"

bool CustomerQueue::IsEmpty() const
{
	return (head == nullptr);
}

void CustomerQueue::Enqueue(const unique_ptr<Customer>& customer)
{
	int priority = customer->CustomerAge() >= 65 ? 1 : 2;

	unique_ptr<Node> newNode = make_unique<Node>(customer, priority);

	if (head == nullptr || priority < head->priority)
	{
		newNode->next = move(head);
		head = move(newNode);
	}
	else
	{
		Node* current = head.get();

		while (current->next != nullptr && priority >= current->next->priority)
		{
			current = current->next.get();
		}

		newNode->next = move(current->next);
		current->next = move(newNode);
	}
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

	cout << "Customer number: " << tempPointer->customer->GetCustomerNumber() << " dequeued from the queue." << endl;

	return tempPointer;
}

void CustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	while (!IsEmpty())
	{
		CustomerQueueIterator customerIterator = begin();
		Customer& customer = *customerIterator;
		mailActionsManager->CallCustomer(customer);
		Dequeue();
	}
}

CustomerQueueIterator CustomerQueue::begin() const
{
	return CustomerQueueIterator(head.get());
}

CustomerQueueIterator CustomerQueue::end() const
{
	return CustomerQueueIterator(nullptr);
}
