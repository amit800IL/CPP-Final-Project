#include "STLCustomerQueue.h"

bool STLCustomerQueue::IsEmpty() const
{
    return customerQueue.empty();
}

void STLCustomerQueue::Enqueue(unique_ptr<Customer> customer)
{
    customerQueue.push_back(move(customer));
}

void STLCustomerQueue::Dequeue(size_t index)
{
    if (index < customerQueue.size())
    {
        customerQueue.erase(customerQueue.begin() + index);
    }
}

void STLCustomerQueue::ServeCustomer(std::shared_ptr<MailCustomerCommunication> mailActionsManager)
{
    bool lastServedRegular = false;

    while (!IsEmpty())
    {
        size_t highestPriorityIndex = FindHighestPriorityCustomerIndex(lastServedRegular);

        if (highestPriorityIndex != std::numeric_limits<size_t>::max())
        {
            auto& highestPriorityCustomer = customerQueue[highestPriorityIndex];
            lastServedRegular = IsRegularCustomer(highestPriorityCustomer);
            ProcessCustomer(highestPriorityCustomer, mailActionsManager);
            Dequeue(highestPriorityIndex);
        }
        else
        {
            break;
        }
    }
}

size_t STLCustomerQueue::FindHighestPriorityCustomerIndex(bool lastServedRegular) const
{
    size_t highestPriorityIndex = std::numeric_limits<size_t>::max();
    int highestPriority = INT_MIN;

    for (size_t i = 0; i < customerQueue.size(); ++i)
    {
        auto& customer = customerQueue[i];

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

    if (lastServedRegular && dynamic_cast<ElderlyCustomer*>(customer.get()) != nullptr)
    {
        priority += 100;
    }

    if (customer->GetAssignedClerk())
    {
        const std::vector<MailActions>& actionSequence = customer->GetAssignedClerk()->GetActionSequence();
        auto it = std::find(actionSequence.begin(), actionSequence.end(), customer->GetCustomerAction());

        if (it != actionSequence.end())
        {
            priority += actionSequence.size() - std::distance(actionSequence.begin(), it);
        }
    }

    return priority;
}

void STLCustomerQueue::ProcessCustomer(const std::unique_ptr<Customer>& customer, std::shared_ptr<MailCustomerCommunication> mailActionsManager)
{
    if (customer)
    {
        customer->Print(std::cout);
        mailActionsManager->CallCustomer(*customer);
    }
}

bool STLCustomerQueue::IsCustomerInDataFile(int customerID) const
{
    std::ifstream customerData("CustomerData.txt");
    bool customerFound = false;
    std::string line;

    while (std::getline(customerData, line))
    {
        if (line.find(std::to_string(customerID)) != std::string::npos)
        {
            std::cout << "Customer number: " << customerID << " found in data file, skipping to next customer." << std::endl;
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

int STLCustomerQueue::findActionIndex(const std::vector<MailActions>& sequence, MailActions action) const
{
    auto it = std::find(sequence.begin(), sequence.end(), action);
    if (it != sequence.end())
    {
        return std::distance(sequence.begin(), it);
    }
    return -1;
}