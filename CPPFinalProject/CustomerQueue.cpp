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
		int highestPriority = 0;

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

int CustomerQueue::CalculateCustomerPriority(bool lastServedRegular, Node* customerNode) const
{
	//Priority for each customer starta always at 0, then based on multiple factors the number updates

	int priority = 0;

	//If i last served regualr customer, and the current customer is eldelry, it adds special amount of priroity score
	//This is meant so the elderly customer will priortized over the factor of action priority

	if (lastServedRegular && IsElderlyCustomer(customerNode))
	{
		priority += 100;
	}

	//Gets the assignend clerk of the specific customer

	const shared_ptr<MailClerk>& clerk = customerNode->customer->GetAssignedClerk();

	//Without it the world will die

	if (clerk != nullptr)
	{
		//Gets the possible actions the clerk has, note: not the ones that are available, this is another vector

		const vector<MailActions>& actionSequence = customerNode->customer->GetAssignedClerk()->GetClerkActions();

		//Gets the specific action the customer choose

		MailActions customerAction = customerNode->customer->GetCustomerAction();

		if (IsRegularCustomer(customerNode))
		{
			//In this case, the priority is being set directly to the value of the priority score for this clerk
			priority = clerk->GivePriorityBasedOnAction(customerAction);
		}
		else if (IsElderlyCustomer(customerNode))
		{
			//In this case, the prioritu is being added to the vale of priority the elder customer has
			//This is to make sure the value of elder customer priority will ovveride the customer action priority
			priority += clerk->GivePriorityBasedOnAction(customerAction);
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

