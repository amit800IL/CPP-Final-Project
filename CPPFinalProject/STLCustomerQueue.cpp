#include "STLCustomerQueue.h"

void STLCustomerQueue::PlaceCustomerInQueue(unique_ptr<Customer> customer)
{
	customerPriorityQueue.push(move(customer));
}

void STLCustomerQueue::GetCustomersFromQueue(shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
	while (!customerPriorityQueue.empty())
	{
		const std::unique_ptr<Customer>& nextCustomer = customerPriorityQueue.top();
		std::cout << "Calling Customer number: " << nextCustomer->GetCustomerNumber() << std::endl;
		cout << "Customer, Age : " << *nextCustomer << endl;
		mailActionsManager->CallCustomer(*nextCustomer);
		customerPriorityQueue.pop();
	}
}

bool STLCustomerQueue::IsEmpty() const
{
	return customerPriorityQueue.empty();
}


