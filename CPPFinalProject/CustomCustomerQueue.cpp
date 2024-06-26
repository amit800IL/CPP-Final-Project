#include "CustomCustomerQueue.h"


bool CustomCustomerQueue::IsEmpty() const
{
	return customerQueueCount <= 0;
}

void CustomCustomerQueue::Enqueue(const unique_ptr<Customer>& customer)
{
	//Created a new node instance, and sets the customer pointer in the consturctor

	unique_ptr<Node> newNode = make_unique<Node>(customer);

	if (head == nullptr)
	{
		//Move head to the adress of new node
		head = move(newNode);
		//Sets the tail to be the head
		tail = head.get();
	}
	else
	{
		//If head is not null, set the tail next node adress to point to the new instance of new node
		tail->next = move(newNode);
		//sets the tail pointer to to be the next node pointer of tail
		tail = tail->next.get();
	}

	customerQueueCount++;
}

void CustomCustomerQueue::Dequeue(Node* current)
{
	//Checks if current customer node is the head

	if (current == head.get())
	{
		//If it is, it moves the head not to the next node variable of head
		//By doing so it deletes the node from the queue
		head = move(head->next);

		if (head == nullptr)
		{
			//Sets the tail to nullptr after head becomes nullptr, so the node is completly deleted from the queue
			tail = nullptr;
		}
	}
	else
	{
		//If current is not the head, it creates a varaible of head to get the previous node
		Node* prev = head.get();

		while (prev != nullptr && prev->next.get() != current)
		{
			//while previoius is not null and not equal to curent
			//it takes the node and sets it to be the next in the queue

			prev = prev->next.get();
		}

		if (prev != nullptr)
		{
			//if previoius node is not null, it moves the previous next node to the adress of the current node
			prev->next = move(current->next);

			if (prev->next == nullptr)
			{
				//If the previous next node is null, it assigns this node to tail, effictevly deleting it form the queue
				tail = prev;
			}
		}
	}

	customerQueueCount--;
}


void CustomCustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	bool lastServedRegular = false;

	while (!IsEmpty())
	{
		Node* current = head.get();
		Node* highestPriorityCustomer = nullptr;
		int highestPriority = 0;

		while (current != nullptr)
		{
			if (!IsCustomerInDataFile(current->customer->GetCustomerID()))
			{
				int currentPriority = CalculateCustomerPriority(lastServedRegular, current);

				//Checkes if the current priority is bigger than the highest priority

				if (currentPriority > highestPriority)
				{
					//if yes, it sets the current priority to the valye of highest priority

					highestPriority = currentPriority;

					//Sets the current customer node, to the highest priority customer node

					highestPriorityCustomer = current;
				}
			}


			//After its done, sets the next node of current

			current = current->next.get();
		}

		if (highestPriorityCustomer != nullptr)
		{
			//if the customer exists, it first sets the lastServedRegular bool to its current state based on the custoemr type
			lastServedRegular = IsRegularCustomer(highestPriorityCustomer);
			//Then it serves the customer
			ProcessCustomer(highestPriorityCustomer, mailActionsManager);

			//Calcultes the waiting and service time

			mailActionsManager->CalculateServiceDuration();
		}
		else
		{
			break;
		}
	}
}

int CustomCustomerQueue::CalculateCustomerPriority(bool lastServedRegular, Node* customerNode) const
{
	//Priority for each customer starta always at 0, then based on multiple factors the number updates

	int priority = 0;

	//If i last served regualr customer, and the current customer is eldelry, it adds special amount of priroity score
	//This is meant so the elderly customer will priortized over the factor of action priority

	if (lastServedRegular && IsElderlyCustomer(customerNode))
	{
		priority += 500;
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

void CustomCustomerQueue::ProcessCustomer(Node* customerNode, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	if (customerNode != nullptr)
	{
		customerNode->customer->Print(cout);
		mailActionsManager->CallCustomer(*customerNode->customer);
		Dequeue(customerNode);
	}
}

bool CustomCustomerQueue::IsCustomerInDataFile(int customerID) const
{
	fstream customerData("CustomerData.txt");
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

bool CustomCustomerQueue::IsRegularCustomer(Node* customerNode) const
{
	if (customerNode && customerNode->customer)
	{
		return dynamic_cast<RegularCustomer*>(customerNode->customer.get()) != nullptr;
	}
	return false;
}

bool CustomCustomerQueue::IsElderlyCustomer(Node* customerNode) const
{
	if (customerNode && customerNode->customer)
	{
		return dynamic_cast<ElderlyCustomer*>(customerNode->customer.get()) != nullptr;
	}
	return false;
}

