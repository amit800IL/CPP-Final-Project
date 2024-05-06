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

	if (head == nullptr)
	{
		tail = nullptr;
	}

	cout << "Customer number: " << head->customer->GetCustomerID()
		<< " dequeued from the queue, Current Amount of Customers: " << customerQueueCount - 1 << endl;
}


void CustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	bool lastServedRegular = false;

	while (!IsEmpty())
	{
		Node* current = head.get();
		Node* highestPriorityCustomer = nullptr;
		int highestPriority = INT_MAX;

		// Open the customer data file inside the loop to reset the stream
		ifstream customerData("CustomerData.txt");

		if (!customerData.is_open())
		{
			cout << "Failed to open customer data file." << endl;
			return;
		}

		while (current)
		{
			string line;
			bool customerFound = false;

			int currentPriority = GetCustomerPriority(current->customer);

			while (getline(customerData, line))
			{
				if (line.find(to_string(current->customer->GetCustomerID())) != string::npos)
				{
					cout << "Customer number: " << current->customer->GetCustomerID()
						<< " found in data file, skipping to next customer." << endl;
					customerFound = true;
					break;
				}
			}

			if (customerFound)
			{
				current = current->next.get();
				continue;
			}


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
		}

		customerData.close(); // Close the file after processing

		if (highestPriorityCustomer)
		{
			lastServedRegular = IsRegularCustomer(highestPriorityCustomer);
			GetCustomerToServe(highestPriorityCustomer, mailActionsManager);
		}
		else
		{
			// If no customer is found to serve, break out of the loop
			break;
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
	if (!a || !b)
		return false;

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

