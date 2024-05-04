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

    nextCustomer->Print(cout);

    if (nextCustomer->GetCustomerAction() != MailActions::Cancel)
    {
        mailActionsManager->CallCustomer(*nextCustomer);
    }
    else 
    {
        cout << " ----- Canceled -----" << std::endl;
    }

    customerQueue.pop();
}

//string STLCustomerQueue::SerializeQueueData(shared_ptr<MailCustomerCommunication> mailActionsManager) const
//{
//	std::stringstream ss;
//
//	while (!regularQueue.empty() || !elderlyQueue.empty()) {
//		if (!regularQueue.empty()) {
//			const Customer& customer = *regularQueue.top();
//			ss << customer.SerializeCustomer() << '\n';
//			mailActionsManager->CallCustomer(customer);
//		}
//		if (!elderlyQueue.empty()) {
//			const Customer& customer = *elderlyQueue.top();
//			ss << customer.SerializeCustomer() << '\n';
//			mailActionsManager->CallCustomer(customer);
//		}
//	}
//
//	return ss.str();
//}

//void STLCustomerQueue::SaveQueueToFile(const std::string& filename, const std::string& serializedData)
//{
//	std::ofstream outputFile(filename);
//	if (outputFile.is_open())
//	{
//		outputFile << serializedData;
//		outputFile.close();
//		std::cout << "Queue data saved to file: " << filename << std::endl;
//	}
//	else
//	{
//		std::cerr << "Unable to open file for writing: " << filename << std::endl;
//	}
//}



///customerQueueRead///

	//fstream customerData("CustomerData.txt");

//string line;

//const unique_ptr<Customer>& nextCustomer = queue.top();

//if (customerData.is_open())
//{
//	while (getline(customerData, line))
//	{
//		if (line.find(to_string(nextCustomer->GetCustomerNumber())) != string::npos)
//		{
//			cout << "Customer found" << endl;
//			customerData.close();
//			return nextCustomer;
//		}
//		else
//		{
//			break;
//		}
//	}
//}

//cout << "Customer not found" << endl;
//cout << *nextCustomer << endl;
//mailActionsManager->CallCustomer(*nextCustomer);
//queue.pop();
//customerData.close();
//return nextCustomer;