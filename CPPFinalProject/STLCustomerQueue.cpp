#include "STLCustomerQueue.h"

void STLCustomerQueue::PlaceCustomerInQueue(unique_ptr<Customer> customer)
{
	customerPriorityQueue.push(move(customer));
}

void STLCustomerQueue::GetCustomersFromQueue(shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
	while (!IsEmpty())
	{

		const unique_ptr<Customer>& topCustomer = customerPriorityQueue.top();

		unique_ptr<Customer> customer = move(const_cast<unique_ptr<Customer>&>(topCustomer));

		cout << "Called Customer number : " << customer->GetCustomerNumber() << endl;

		mailActionsManager->CallCustomer(*customer);

		customerPriorityQueue.pop();
	}
}

bool STLCustomerQueue::IsEmpty() const
{
	return customerPriorityQueue.empty();
}


