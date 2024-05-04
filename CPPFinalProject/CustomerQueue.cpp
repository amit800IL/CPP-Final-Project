#include "CustomerQueue.h"


bool CustomerQueue::IsEmpty() const
{
	return customerQueueCount <= 0;
}

void CustomerQueue::Enqueue(const unique_ptr<Customer>& customer)
{
    auto newNode = make_unique<Node>(customer);

    if (!head)
    {
        head = move(newNode);
    }
    else
    {
        Node* current = head.get();
        while (current->next)
        {
            current = current->next.get();
        }
        current->next = move(newNode);
    }

    customerQueueCount++;
}

void CustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
    bool lastServedRegular = false;

    while (!IsEmpty())
    {
        Node* highestPriorityCustomer = nullptr;
        int highestPriority = INT_MAX;

        Node* current = head.get();
        while (current)
        {
            int currentPriority = GetCustomerPriority(current->customer);

            if (lastServedRegular && IsElderlyCustomer(current))
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

