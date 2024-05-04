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

	bool lastServedRegular = false;

	while (!IsEmpty())
	{
		Node* current = head.get();

		int highestPriority = INT_MAX; 
		Node* highestPriorityCustomer = nullptr;

		while (current != nullptr)
		{
			int currentPriority = GetCustomerPriority(current->customer);

			if (lastServedRegular && dynamic_cast<ElderlyCustomer*>(current->customer.get()) != nullptr)
			{
				currentPriority -= 100;
			}

			if (currentPriority < highestPriority)
			{
				highestPriority = currentPriority;
				highestPriorityCustomer = current;
			}

			current = current->next.get();
		}

		if (highestPriorityCustomer != nullptr)
		{
			if (dynamic_cast<RegularCustomer*>(highestPriorityCustomer->customer.get()) != nullptr)
			{
				lastServedRegular = true;
			}
			else
			{
				lastServedRegular = false;
			}

			GetCustomerToServe(highestPriorityCustomer, mailActionsManager);
		}
	}
}

int CustomerQueue::GetCustomerPriority(const unique_ptr<Customer>& customer) const
{
	shared_ptr<MailClerk> clerk = customer->GetAssignedClerk();

	if (clerk != nullptr) 
	{
		const vector<MailActions>& actionSequence = clerk->GetActionSequence();
		MailActions chosenAction = customer->GetCustomerAction();

		int actionPriority = findActionIndex(actionSequence, chosenAction);

		if (actionPriority != -1) 
		{
			return actionPriority;
		}
	}

	return customer->CustomerAge();
}

int CustomerQueue::findActionIndex(const vector<MailActions>& sequence, MailActions action) const
{
	auto it = find(sequence.begin(), sequence.end(), action);
	if (it != sequence.end()) {
		return distance(sequence.begin(), it);
	}
	return -1;
}

void CustomerQueue::GetCustomerToServe(Node* current, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	current->customer->Print(cout);
	mailActionsManager->CallCustomer(*current->customer);
	customerQueueCount--;

	cout << "Customer number: " << current->customer->GetCustomerNumber()
		<< " dequeued from the queue, Current Amount of Customers: " << customerQueueCount << endl;

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
