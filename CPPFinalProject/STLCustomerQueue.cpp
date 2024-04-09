#include "STLCustomerQueue.h"
void STLCustomerQueue::PlaceCustomerInQueue(std::unique_ptr<Customer> customer) {
	if (dynamic_cast<ElderlyCustomer*>(customer.get()) != nullptr)
	{
		elderlyQueue.push(std::move(customer));
	}
	else if (dynamic_cast<RegularCustomer*>(customer.get()) != nullptr)
	{
		regularQueue.push(std::move(customer));
	}
}

void STLCustomerQueue::GetCustomersFromQueue(shared_ptr<IServiceCustomerMediator> mailActionsManager) {
	while (!regularQueue.empty() || !elderlyQueue.empty())
	{
		if (!regularQueue.empty()) {
			ServeNextCustomer(regularQueue, mailActionsManager);
		}
		if (!elderlyQueue.empty()) 
		{
			ServeNextCustomer(elderlyQueue, mailActionsManager);
		}
	}
}

bool STLCustomerQueue::IsEmpty() const
{
	return regularQueue.empty() && elderlyQueue.empty();
}


void STLCustomerQueue::ServeNextCustomer(std::priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerComparator>& queue, shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
	const std::unique_ptr<Customer>& nextCustomer = queue.top();
	std::cout << "Calling Customer number: " << nextCustomer->GetCustomerNumber() << std::endl;
	cout << "Customer, Age : " << *nextCustomer << endl;
	mailActionsManager->CallCustomer(*nextCustomer);
	queue.pop();
}
