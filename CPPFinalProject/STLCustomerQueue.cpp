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

        if (Customer* regularCustomer = dynamic_cast<RegularCustomer*>(nextCustomer.get()))
        {
            cout << "Regular Customer, Age : " << regularCustomer->CustomerAge() << endl;
            mailActionsManager->CallCustomer(*regularCustomer);
        }
        else if (Customer* elderlyCustomer = dynamic_cast<ElderlyCustomer*>(nextCustomer.get()))
        {
            cout << "Elderly Customer, Age : " << elderlyCustomer->CustomerAge() << endl;
            mailActionsManager->CallCustomer(*elderlyCustomer);
        }

        customerPriorityQueue.pop();
    }
}




bool STLCustomerQueue::IsEmpty() const
{
	return customerPriorityQueue.empty();
}


