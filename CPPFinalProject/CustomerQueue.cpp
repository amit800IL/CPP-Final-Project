#include "CustomerQueue.h"


bool CustomerQueue::IsEmpty() const
{
	return customerQueueCount <= 0;
}

void CustomerQueue::Enqueue(const unique_ptr<Customer>& customer)
{
	int priority;

	unique_ptr<Node> newNode = make_unique<Node>(customer, priority);

	if (dynamic_cast<ElderlyCustomer*>(customer.get()) != nullptr)
	{
		priority = 2;
	}
	else if (dynamic_cast<RegularCustomer*>(customer.get()) != nullptr)
	{
		priority = 1;
	}

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

	customerQueueCount++;
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

	customerQueueCount--;

	cout << "Customer number: " << tempPointer->customer->GetCustomerNumber() << " dequeued from the queue, Current Amount of Customers :" << customerQueueCount << endl;

	return tempPointer;
}

void CustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	bool servedRegular = false;
	bool servedElderly = false;

	while (!IsEmpty())
	{
		if (servedRegular) {
			Node* current = head.get();
			while (current != nullptr) 
			{
				if (dynamic_cast<ElderlyCustomer*>(current->customer.get()) != nullptr)
				{
					cout << *current->customer << endl;
					mailActionsManager->CallCustomer(*current->customer);

					if (current == head.get()) {
						head = move(head->next);
					}
					else
					{
						Node* prev = head.get();
						while (prev->next.get() != current)
						{
							prev = prev->next.get();
						}
						prev->next = move(current->next);
					}
					servedElderly = true;
					servedRegular = false;
					break; 
				}
				current = current->next.get();
			}
		}

		if (servedElderly || (!servedRegular && !servedElderly))
		{
			Node* current = head.get();
			while (current != nullptr) 
			{
				if (dynamic_cast<RegularCustomer*>(current->customer.get()) != nullptr) {
					cout << *current->customer << endl;
					mailActionsManager->CallCustomer(*current->customer);

					if (current == head.get()) {
						head = move(head->next);
					}
					else
					{
						Node* prev = head.get();
						while (prev->next.get() != current) {
							prev = prev->next.get();
						}
						prev->next = move(current->next);
					}
					servedRegular = true;
					servedElderly = false;
					break;
				}
				current = current->next.get();
			}
		}
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
