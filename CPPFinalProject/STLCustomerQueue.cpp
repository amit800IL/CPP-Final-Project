#include "STLCustomerQueue.h"

void STLCustomerQueue::Enqueue(std::unique_ptr<Customer> customer)
{
    customerPriorityQueue.push(std::move(customer));
    std::cout << "Customer enqueued to the priority queue." << std::endl;
}

void STLCustomerQueue::Dequeue()
{
    if (!customerPriorityQueue.empty()) {
        std::cout << "Customer dequeued from the priority queue." << std::endl;
        customerPriorityQueue.pop();
    }
    else
    {
        std::cout << "Priority queue is empty." << std::endl;
    }
}

bool STLCustomerQueue::IsEmpty() const
{
    return customerPriorityQueue.empty();
}
