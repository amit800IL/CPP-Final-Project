#include "STLCustomerQueue.h"

void STLCustomerQueue::PlaceCustomerInQueue(unique_ptr<Customer> customer)
{
	customerPriorityQueue.push(move(customer));
}

void STLCustomerQueue::GetCustomersFromQueue(shared_ptr<IServiceCustomerMediator> mailActionsManager)
{
    bool serveElderlyNext = false;

    while (!customerPriorityQueue.empty())
    {
        const unique_ptr<Customer>& nextCustomer = customerPriorityQueue.top();

        if (nextCustomer->CustomerAge() > 65 && serveElderlyNext)
        {
            cout << "Calling Elderly Customer number: " << nextCustomer->GetCustomerNumber() << endl;
            mailActionsManager->CallCustomer(*nextCustomer);
            customerPriorityQueue.pop();
            serveElderlyNext = false; 
        }
        else if (nextCustomer->CustomerAge() <= 65 && !serveElderlyNext)
        {
            // Serve regular customer
            cout << "Calling Regular Customer number: " << nextCustomer->GetCustomerNumber() << endl;
            mailActionsManager->CallCustomer(*nextCustomer);
            customerPriorityQueue.pop();
            serveElderlyNext = true; 
        }
        else
        {
            customerPriorityQueue.pop(); 
        }
    }
}




bool STLCustomerQueue::IsEmpty() const
{
	return customerPriorityQueue.empty();
}


