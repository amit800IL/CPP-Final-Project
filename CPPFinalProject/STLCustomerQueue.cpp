#include "STLCustomerQueue.h"
void STLCustomerQueue::PlaceCustomerInQueue(unique_ptr<Customer> customer) {
	if (dynamic_cast<ElderlyCustomer*>(customer.get()) != nullptr)
	{
		elderlyQueue.push(std::move(customer));
	}
	else if (dynamic_cast<RegularCustomer*>(customer.get()) != nullptr)
	{
		regularQueue.push(std::move(customer));
	}
}

void STLCustomerQueue::GetCustomersFromQueue(shared_ptr<MailCustomerCommunication> mailActionsManager) {
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


void STLCustomerQueue::ServeNextCustomer(std::priority_queue<unique_ptr<Customer>, vector<unique_ptr<Customer>>, CustomerComparator>& queue, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	const unique_ptr<Customer>& nextCustomer = queue.top();
	std::cout << "Calling Customer number: " << nextCustomer->GetCustomerNumber() << std::endl;
	cout << "Customer, Age : " << *nextCustomer << endl;
	mailActionsManager->CallCustomer(*nextCustomer);
	queue.pop();
}

const Customer& STLCustomerQueue::GetNextCustomer() const
{
	if (!regularQueue.empty())
	{
		return *regularQueue.top();
	}
	else if (!elderlyQueue.empty())
	{
		return *elderlyQueue.top();
	}

	throw std::logic_error("No customer available");
}

string STLCustomerQueue::SerializeQueueData(shared_ptr<MailCustomerCommunication> mailActionsManager) const
{
	std::stringstream ss;

	while (!regularQueue.empty() || !elderlyQueue.empty()) {
		if (!regularQueue.empty()) {
			const Customer& customer = *regularQueue.top();
			ss << customer.SerializeCustomer() << '\n';
			mailActionsManager->CallCustomer(customer);
		}
		if (!elderlyQueue.empty()) {
			const Customer& customer = *elderlyQueue.top();
			ss << customer.SerializeCustomer() << '\n';
			mailActionsManager->CallCustomer(customer);
		}
	}

	return ss.str();
}

void STLCustomerQueue::SaveQueueToFile(const std::string& filename, const std::string& serializedData)
{
	std::ofstream outputFile(filename);
	if (outputFile.is_open())
	{
		outputFile << serializedData;
		outputFile.close();
		std::cout << "Queue data saved to file: " << filename << std::endl;
	}
	else
	{
		std::cerr << "Unable to open file for writing: " << filename << std::endl;
	}
}