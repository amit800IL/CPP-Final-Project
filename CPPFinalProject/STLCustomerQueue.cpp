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

		//Gets the high value customer from the queue by index

		const unique_ptr<Customer>& highestPriorityCustomer = customerQueue[highestPriorityIndex];

		//Saving the world again

		if (highestPriorityCustomer != nullptr)
		{
			//Sets the last served regualr bool value to either true or false based on the customer type

			lastServedRegular = IsRegularCustomer(highestPriorityCustomer);

			//The serving itself of the customer

			ProcessCustomer(highestPriorityCustomer, mailActionsManager);

			//Calcultes the hour of service and amount of waiting time

			mailActionsManager->CalculateServiceDuration();

			//removes the customer

			Dequeue(highestPriorityIndex);
		}
	}
}

int STLCustomerQueue::FindHighestPriorityCustomerIndex(bool lastServedRegular) const
{
	int highestPriorityIndex = 0;
	int highestPriority = 0;

	for (int i = 0; i < customerQueue.size(); ++i)
	{
		//Gets the High priority customer

		const unique_ptr<Customer>& customer = customerQueue[i];

		//Checks if the customer is in the data file

		if (!IsCustomerInDataFile(customer->GetCustomerID()))
		{
			//If the customer is not on the data file, the customer priority is calculted for service

			int currentPriority = CalculateCustomerPriority(lastServedRegular, customer);

			//if the current priority is bigger then minmum required priority, it enters

			if (currentPriority > highestPriority)
			{
				//Then it sets the current priority of the customer to the highest priority

				highestPriority = currentPriority;

				//Then it sets the priority indes of the customer to the high priority index so it will get the customer

				highestPriorityIndex = i;
			}
		}
	}

	return highestPriorityIndex;
}

int STLCustomerQueue::CalculateCustomerPriority(bool lastServedRegular, const unique_ptr<Customer>& customer) const
{
	//Priority for each customer starta always at 0, then based on multiple factors the number updates

	int priority = 0;

	//If i last served regualr customer, and the current customer is eldelry, it adds special amount of priroity score
	//This is meant so the elderly customer will priortized over the factor of action priority

	if (lastServedRegular && IsElderlyCustomer(customer))
	{
		priority += 500;
	}

	//Gets the assignend clerk of the specific customer

	const shared_ptr<MailClerk>& clerk = customer->GetAssignedClerk();

	//Without it the world will die

	if (clerk != nullptr)
	{
		//Gets the possible actions the clerk has, note: not the ones that are available, this is another vector

		const vector<MailActions>& actionSequence = customer->GetAssignedClerk()->GetClerkActions();

		//Gets the specific action the customer choose

		MailActions customerAction = customer->GetCustomerAction();

		if (IsRegularCustomer(customer))
		{
			//In this case, the priority is being set directly to the value of the priority score for this clerk
			priority = clerk->GivePriorityBasedOnAction(customerAction);
		}
		else if (IsElderlyCustomer(customer))
		{
			//In this case, the prioritu is being added to the vale of priority the elder customer has
			//This is to make sure the value of elder customer priority will ovveride the customer action priority
			priority += clerk->GivePriorityBasedOnAction(customerAction);
		}
	}


	return priority;
}

void STLCustomerQueue::ProcessCustomer(const unique_ptr<Customer>& customer, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	if (customer != nullptr)
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
