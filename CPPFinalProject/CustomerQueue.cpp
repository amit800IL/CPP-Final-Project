#include "CustomerQueue.h"


bool CustomerQueue::IsEmpty() const
{
	return customerQueueCount <= 0;
}

void CustomerQueue::Enqueue(const unique_ptr<Customer>& customer)
{
	unique_ptr<Node> newNode = make_unique<Node>(customer);

	if (!head)
	{
		head = move(newNode);
		tail = head.get();
	}
	else
	{
		tail->next = move(newNode);
		tail = tail->next.get();
	}

	customerQueueCount++;
}

void CustomerQueue::Dequeue(Node* current)
{
	if (current == head.get())
	{
		head = move(head->next);

		if (!head)
		{
			tail = nullptr;
		}
	}
	else
	{
		Node* prev = head.get();
		while (prev && prev->next.get() != current)
		{
			prev = prev->next.get();
		}
		if (prev)
		{
			prev->next = move(current->next);

			if (prev->next == nullptr)
			{
				tail = prev;
			}
		}
	}

	customerQueueCount--;
}


void CustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	bool lastServedRegular = false;

	while (!IsEmpty())
	{
		Node* current = head.get();
		Node* highestPriorityCustomer = nullptr;
		int highestPriority = INT_MIN;

		while (current)
		{
			if (!IsCustomerInDataFile(current->customer->GetCustomerID()))
			{
				int currentPriority = CalculateCustomerPriority(lastServedRegular, current);

				if (currentPriority > highestPriority)
				{
					highestPriority = currentPriority;
					highestPriorityCustomer = current;
				}
			}

			current = current->next.get();
		}

		if (highestPriorityCustomer)
		{
			lastServedRegular = IsRegularCustomer(highestPriorityCustomer);
			ProcessCustomer(highestPriorityCustomer, mailActionsManager);
		}
		else
		{
			break; 
		}
	}
}

int CustomerQueue::CalculateCustomerPriority(bool lastServedRegular, Node* node) const
{
	int priority = 0;

	if (lastServedRegular && IsElderlyCustomer(node))
	{
		priority += 100;
	}

	if (node->customer->GetAssignedClerk())
	{
		const vector<MailActions>& actionSequence = node->customer->GetAssignedClerk()->GetActionSequence();
		int index = findActionIndex(actionSequence, node->customer->GetCustomerAction());

		if (index != -1)
		{
			priority += actionSequence.size() - index; 
		}
	}

	return priority;
}

void CustomerQueue::ProcessCustomer(Node* customerNode, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	if (customerNode)
	{
		customerNode->customer->Print(cout);
		mailActionsManager->CallCustomer(*customerNode->customer);
		Dequeue(customerNode);
	}
}

bool CustomerQueue::IsCustomerInDataFile(int customerID) const
{
	ifstream customerData("CustomerData.txt");
	bool customerFound = false;
	string line;

	while (getline(customerData, line))
	{
		if (line.find(to_string(customerID)) != string::npos)
		{
			cout << "Customer number: " << customerID << " found in data file, skipping to next customer." << endl;
			customerFound = true;
			break;
		}
	}

	customerData.close();
	return customerFound;
}

bool CustomerQueue::IsRegularCustomer(Node* customerNode) const
{
	if (customerNode && customerNode->customer)
	{
		return dynamic_cast<RegularCustomer*>(customerNode->customer.get()) != nullptr;
	}
	return false;
}

bool CustomerQueue::IsElderlyCustomer(Node* customerNode) const
{
	if (customerNode && customerNode->customer)
	{
		return dynamic_cast<ElderlyCustomer*>(customerNode->customer.get()) != nullptr;
	}
	return false;
}

int CustomerQueue::findActionIndex(const vector<MailActions>& sequence, MailActions action) const
{
	auto it = find(sequence.begin(), sequence.end(), action);
	if (it != sequence.end())
	{
		return distance(sequence.begin(), it);
	}
	return -1;
}


