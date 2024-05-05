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
		tail = head.get();

		while (tail->next)
		{
			tail = tail->next.get();
		}

		tail->next = move(newNode);
	}

	customerQueueCount++;
}

void CustomerQueue::Dequeue()
{
	if (IsEmpty())
	{
		cout << "Queue is empty. Cannot dequeue." << endl;
		return;
	}


	head = move(head->next);

	cout << "Customer number: " << head->customer->GetPriorityScore()
		<< " dequeued from the queue, Current Amount of Customers: " << customerQueueCount - 1 << endl;
}


void CustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	bool lastServedRegular = false;

	fstream customerData("CustomerData.txt");

	while (!IsEmpty())
	{
		Node* current = head.get();
		Node* highestPriorityCustomer = nullptr;
		int highestPriority = INT_MAX;
		bool customerFound = false;
		string line;

		/*	if (!customerData.is_open())
				return;

			while (getline(customerData, line))
			{
				if (current != nullptr && line.find(to_string(current->customer->GetPriorityScore())) != std::string::npos)
				{
					cout << "Customer number: " << current->customer->GetPriorityScore() << ", found ,skipping to next customer " << endl;
					customerFound = true;
					break;
				}
			}

			customerData.close();*/

		while (current)
		{
			/*if (customerFound)
			{
				break;
			}*/

			/*if (!customerFound)
			{*/
			cout << "Customer not found, serving...." << endl;

			int currentPriority = GetCustomerPriority(current->customer);

			if (IsElderlyCustomer(current) && lastServedRegular)
			{
				currentPriority -= 100;
			}

			if (currentPriority < highestPriority)
			{
				highestPriority = currentPriority;
				highestPriorityCustomer = current;
			}

			current = current->next.get();

			//}

		}

		if (highestPriorityCustomer)
		{
			lastServedRegular = IsRegularCustomer(highestPriorityCustomer);
			GetCustomerToServe(highestPriorityCustomer, mailActionsManager);
		}
	}

}



int CustomerQueue::GetCustomerPriority(const unique_ptr<Customer>& customer) const
{
	// Use the custom comparison function for priority logic
	return CustomerPriorityCompare(customer, nullptr); // Compare against nullptr for simplicity
}

bool CustomerQueue::CustomerPriorityCompare(const unique_ptr<Customer>& a, const unique_ptr<Customer>& b) const
{
	if (!a)
		return false;
	if (!b)
		return true;

	shared_ptr<MailClerk> clerkA = a->GetAssignedClerk();
	shared_ptr<MailClerk> clerkB = b->GetAssignedClerk();

	if (clerkA && clerkB)
	{
		const vector<MailActions>& actionSequenceA = clerkA->GetActionSequence();
		const vector<MailActions>& actionSequenceB = clerkB->GetActionSequence();

		int indexA = findActionIndex(actionSequenceA, a->GetCustomerAction());
		int indexB = findActionIndex(actionSequenceB, b->GetCustomerAction());

		if (indexA != -1 && indexB != -1)
		{
			return indexA > indexB;
		}
	}

	return a->CustomerAge() > b->CustomerAge();
}


void CustomerQueue::GetCustomerToServe(Node* current, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	current->customer->Print(cout);
	mailActionsManager->CallCustomer(*current->customer);

	if (current == head.get())
	{
		head = move(head->next);
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
		}
	}
}

bool CustomerQueue::IsRegularCustomer(Node* customerNode) const
{
	return dynamic_cast<RegularCustomer*>(customerNode->customer.get()) != nullptr;
}

bool CustomerQueue::IsElderlyCustomer(Node* customerNode) const
{
	return dynamic_cast<ElderlyCustomer*>(customerNode->customer.get()) != nullptr;
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

