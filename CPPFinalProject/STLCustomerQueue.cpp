#include "STLCustomerQueue.h"

bool STLCustomerQueue::IsEmpty() const
{
	return customerQueue.empty();
}

void STLCustomerQueue::Enqueue(unique_ptr<Customer> customer)
{
	customerQueue.push_back(move(customer));
}

void STLCustomerQueue::Dequeue(int index)
{
	if (index < customerQueue.size())
	{
		customerQueue.erase(customerQueue.begin() + index);
	}
}

void STLCustomerQueue::ServeCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	bool lastServedRegular = false;

	while (!IsEmpty())
	{
		int highestPriorityIndex = FindHighestPriorityCustomerIndex(lastServedRegular);

		if (highestPriorityIndex != INT_MAX)
		{
			const unique_ptr<Customer>& highestPriorityCustomer = customerQueue[highestPriorityIndex];
			lastServedRegular = IsRegularCustomer(highestPriorityCustomer);
			ProcessCustomer(highestPriorityCustomer, mailActionsManager);
			mailActionsManager->CalculateServiceDuration();
			Dequeue(highestPriorityIndex);
		}
		else
		{
			break;
		}
	}
}

int STLCustomerQueue::FindHighestPriorityCustomerIndex(bool lastServedRegular) const
{
	int highestPriorityIndex = INT_MAX;
	int highestPriority = INT_MIN;

	for (int i = 0; i < customerQueue.size(); ++i)
	{
		const unique_ptr<Customer>& customer = customerQueue[i];

		if (!IsCustomerInDataFile(customer->GetCustomerID()))
		{
			int currentPriority = CalculateCustomerPriority(lastServedRegular, customer);

			if (currentPriority > highestPriority)
			{
				highestPriority = currentPriority;
				highestPriorityIndex = i;
			}
		}
	}

	return highestPriorityIndex;
}

int STLCustomerQueue::CalculateCustomerPriority(bool lastServedRegular, const unique_ptr<Customer>& customer) const
{
	int priority = 0;

	if (lastServedRegular && IsElderlyCustomer(customer))
	{
		priority += 100;
	}

	const shared_ptr<MailClerk>& clerk = customer->GetAssignedClerk();

	if (clerk != nullptr)
	{
		const vector<MailActions>& actionSequence = customer->GetAssignedClerk()->GetActionSequence();
		MailActions customerAction = customer->GetCustomerAction();

		if (IsRegularCustomer(customer))
		{
			priority = clerk->GivePriorityBasedOnAction(customerAction);
		}
		else if (IsElderlyCustomer(customer))
		{
			priority += clerk->GivePriorityBasedOnAction(customerAction);
		}
	}


	return priority;
}

void STLCustomerQueue::ProcessCustomer(const unique_ptr<Customer>& customer, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	if (customer)
	{
		customer->Print(cout);
		mailActionsManager->CallCustomer(*customer);
	}
}

bool STLCustomerQueue::IsCustomerInDataFile(int customerID) const
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

bool STLCustomerQueue::IsRegularCustomer(const unique_ptr<Customer>& customer) const
{
	return dynamic_cast<RegularCustomer*>(customer.get()) != nullptr;
}

bool STLCustomerQueue::IsElderlyCustomer(const unique_ptr<Customer>& customer) const
{
	return dynamic_cast<ElderlyCustomer*>(customer.get()) != nullptr;
}
