#include "CustomerQueue.h"


bool CustomerQueue::IsEmpty() const
{
	return customerQueueCount <= 0;
}

void CustomerQueue::Enqueue(const unique_ptr<Customer>& customer)
{
	unique_ptr<Node> newNode = make_unique<Node>(customer);

	if (head == nullptr)
	{
		newNode->next = move(head);
		head = move(newNode);
	}
	else
	{

		Node* current = head.get();

		while (current->next != nullptr)
		{
			current = current->next.get();
		}

		newNode->next = move(current->next);
		current->next = move(newNode);
	}

	customerQueueCount++;
}


void CustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	bool servedRegular = false;
	bool servedElderly = false;

	while (!IsEmpty())
	{
		if (servedRegular)
		{
			Node* current = head.get();
			while (current != nullptr && current->customer != nullptr)
			{
				if (dynamic_cast<ElderlyCustomer*>(current->customer.get()) != nullptr)
				{
					GetCustomerToServe(current, mailActionsManager);
					servedElderly = true;
					servedRegular = false;
					break;
				}
				current = current->next.get();
			}
		}

		else if (servedElderly || (!servedRegular && !servedElderly))
		{
			Node* current = head.get();
			while (current != nullptr && current->customer != nullptr)
			{
				if (dynamic_cast<RegularCustomer*>(current->customer.get()) != nullptr)
				{
					GetCustomerToServe(current, mailActionsManager);
					servedElderly = false;
					servedRegular = true;
					break;  
				}
				current = current->next.get();
			}
		}
	}

}




void CustomerQueue::GetCustomerToServe(Node* current, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	current->customer->Print(cout);

	mailActionsManager->CallCustomer(*current->customer);

	customerQueueCount--;

	cout << "Customer number: " << current->customer->GetCustomerNumber() << " dequeued from the queue, Current Amount of Customers :" << customerQueueCount << endl;

	if (current == head.get())
	{
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
}

CustomerQueueIterator CustomerQueue::begin() const
{
	return CustomerQueueIterator(head.get());
}

CustomerQueueIterator CustomerQueue::end() const
{
	return CustomerQueueIterator(nullptr);
}
