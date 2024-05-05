#include "STLCustomerQueue.h"
void STLCustomerQueue::PlaceCustomerInQueue(unique_ptr<Customer> customer)
{
	customerQueue.push(std::move(customer));
}

void STLCustomerQueue::GetCustomersFromQueue(shared_ptr<MailCustomerCommunication> mailActionsManager) {
	while (!customerQueue.empty())
	{
		ServeNextCustomer(mailActionsManager);
	}
}

bool STLCustomerQueue::IsEmpty() const {
	return customerQueue.empty();
}

const Customer& STLCustomerQueue::GetNextCustomer() const {
	if (!customerQueue.empty())
	{
		return *customerQueue.top();
	}
	throw std::logic_error("No customer available");
}

void STLCustomerQueue::ServeNextCustomer(shared_ptr<MailCustomerCommunication> mailActionsManager) {

	const unique_ptr<Customer>& nextCustomer = customerQueue.top();

	std::fstream customerData("CustomerData.txt");


	std::string line;
	bool customerFound = false;

	if (customerData.is_open())
	{
		while (getline(customerData, line))
		{
			if (line.find(std::to_string(nextCustomer->GetPriorityScore())) != std::string::npos) {

				cout << "Customer found: ";
				nextCustomer->Print(cout);

				if (nextCustomer->GetCustomerAction() != MailActions::Cancel)
				{

					std::cout << "Customer already served" << std::endl;
				}
				else
				{
					std::cout << "Customer action canceled" << std::endl;
				}

				customerQueue.pop();
				customerFound = true;
				break;
			}

			customerData.close();
		}

		if (!customerFound)
		{
			cout << "Customer not found in the data file:";
			nextCustomer->Print(cout);
			mailActionsManager->CallCustomer(*nextCustomer);
			customerQueue.pop();
		}
	}
}