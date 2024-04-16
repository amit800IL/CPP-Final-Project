
#include "Customer.h";
#include "CustomerQueue.h"
#include "CustomerQueueIterator.h"
#include "MailClerk.h"
#include "MailCustomerCommunication.h"
#include "STLCustomerQueue.h"
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <fstream>
using namespace std;

void PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
void UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager);
void BaseSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);
void CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager);

//std::string SerializeQueueData(shared_ptr<MailCustomerCommunication> mailActionsManager, const STLCustomerQueue& queue);
//void SaveQueueToFile(const std::string& filename, const std::string& serializedData);
////std::string SerializeCustomer(const Customer& customer);
//Customer DeserializeCustomer(const std::string& data);

int main()
{
	vector<shared_ptr<MailClerk>> clerks;

	unordered_set<MailActions> clerk1Actions = { MailActions::RecivePackage, MailActions::MakePayment,  MailActions::DeliverPackage, MailActions::PurchaseProduct };
	unordered_set<MailActions> clerk2Actions = { MailActions::RecivePackage, MailActions::MakePayment , MailActions::PurchaseProduct };
	unordered_set<MailActions> clerk3Actions = { MailActions::PurchaseProduct, MailActions::MakePayment };
	unordered_set<MailActions> clerk4Actions = { MailActions::RecivePackage, MailActions::DeliverPackage };

	shared_ptr<MailClerk> mailClerk1 = make_shared<MailClerk>(1, clerk1Actions);
	shared_ptr<MailClerk> mailClerk2 = make_shared<MailClerk>(2, clerk2Actions);
	shared_ptr<MailClerk> mailClerk3 = make_shared<MailClerk>(3, clerk3Actions);
	shared_ptr<MailClerk> mailClerk4 = make_shared<MailClerk>(4, clerk4Actions);

	clerks.push_back(mailClerk1);
	clerks.push_back(mailClerk2);
	clerks.push_back(mailClerk3);
	clerks.push_back(mailClerk4);

	shared_ptr<MailCustomerCommunication> mailActionsManager = make_shared<MailCustomerCommunication>(clerks);

	char input = ' ';

	PickAndUseSystem(input, mailActionsManager);

	return 0;
}

void PickAndUseSystem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	cout << "Hello, welcome to your line managment system, please choose the system you want to use: " << endl;

	cout << "1.Use basic line managment system(STL)" << endl;
	cout << "2.Use custom line managment system(custom STL)" << endl;

	while (input != '1' && input != '2')
	{
		cin >> input;

		if (input == '1')
		{
			cout << "Customers inserted" << endl;
		}
		else if (input == '2')
		{
			cout << "Good choice, here are the customers that are waiting: " << endl;
		}
	}

	UseSytem(input, mailActionsManager);
}

void UseSytem(char input, shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	if (input == '1')
	{
		BaseSTL(mailActionsManager);
	}

	else if (input == '2')
	{
		CustomSTL(mailActionsManager);
	}
}

void BaseSTL(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	unique_ptr<STLCustomerQueue> stlCustomerQueue = make_unique<STLCustomerQueue>();

	unique_ptr<DateOfBirth> birthDate1 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(10, 9, 2010);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(11, 10, 2007);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate5 = make_unique<DateOfBirth>(5, 6, 1950);
	unique_ptr<DateOfBirth> birthDate6 = make_unique<DateOfBirth>(17, 3, 1950);
	unique_ptr<DateOfBirth> birthDate7 = make_unique<DateOfBirth>(17, 3, 1940);
	unique_ptr<DateOfBirth> birthDate8 = make_unique<DateOfBirth>(17, 3, 2010);

	unique_ptr<Customer> customer1 = make_unique<RegularCustomer>(*birthDate1);
	unique_ptr<Customer> customer2 = make_unique<RegularCustomer>(*birthDate2);
	unique_ptr<Customer> customer3 = make_unique<RegularCustomer>(*birthDate3);
	unique_ptr<Customer> customer4 = make_unique<RegularCustomer>(*birthDate4);
	unique_ptr<Customer> customer5 = make_unique<ElderlyCustomer>(*birthDate5);
	unique_ptr<Customer> customer6 = make_unique<ElderlyCustomer>(*birthDate6);
	unique_ptr<Customer> customer7 = make_unique<ElderlyCustomer>(*birthDate7);
	unique_ptr<Customer> customer8 = make_unique<ElderlyCustomer>(*birthDate8);

	stlCustomerQueue->PlaceCustomerInQueue(move(customer1));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer2));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer3));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer4));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer5));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer6));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer7));
	stlCustomerQueue->PlaceCustomerInQueue(move(customer8));

	stlCustomerQueue->GetCustomersFromQueue(mailActionsManager);

	//std::string serializedData = SerializeQueueData(mailActionsManager, *stlCustomerQueue);

	//std::string filename = "customer_queue_data.txt";
	//SaveQueueToFile(filename, serializedData);
}

void CustomSTL(shared_ptr<MailCustomerCommunication> mailActionsManager)
{
	shared_ptr<CustomerQueue> customerQueue = make_shared<CustomerQueue>();

	unique_ptr<DateOfBirth> birthDate = make_unique<DateOfBirth>(11, 12, 1998);
	unique_ptr<DateOfBirth> birthDate2 = make_unique<DateOfBirth>(17, 3, 1950);
	unique_ptr<DateOfBirth> birthDate3 = make_unique<DateOfBirth>(3, 1, 2000);
	unique_ptr<DateOfBirth> birthDate4 = make_unique<DateOfBirth>(17, 3, 1940);

	unique_ptr<Customer> customer = make_unique<RegularCustomer>(*birthDate);
	unique_ptr<Customer> customer2 = make_unique<ElderlyCustomer>(*birthDate2);
	unique_ptr<Customer> customer3 = make_unique<RegularCustomer>(*birthDate3);
	unique_ptr<Customer> customer4 = make_unique<ElderlyCustomer>(*birthDate4);

	customerQueue->Enqueue(move(*customer));
	customerQueue->Enqueue(move(*customer2));
	customerQueue->Enqueue(move(*customer3));
	customerQueue->Enqueue(move(*customer4));

	while (!customerQueue->IsEmpty())
	{
		CustomerQueueIterator customerIterator = customerQueue->begin();
		Customer& customer = *customerIterator;
		mailActionsManager->CallCustomer(customer);
		customerQueue->Dequeue();
	}
}
//}
//std::string SerializeQueueData(shared_ptr<MailCustomerCommunication> mailActionsManager, const STLCustomerQueue& queue)
//{
//	std::stringstream ss;
//	STLCustomerQueue queueCopy(std::move(queue)); // Create a copy to iterate over
//	while (!queueCopy.IsEmpty())
//	{
//		//const Customer& customer = queueCopy.GetNextCustomer();
//		//std::string serializedCustomer = SerializeCustomer(move(customer));
//		//ss << serializedCustomer << '\n';
//		queueCopy.GetCustomersFromQueue(mailActionsManager); // Move to the next customer in the queue
//	}
//	return ss.str();
//}

// Save serialized queue data to a text file
//void SaveQueueToFile(const std::string& filename, const std::string& serializedData)
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

//std::string SerializeCustomer(const Customer& customer) {
//	std::stringstream ss;
//	ss << customer.GetCustomerNumber() << ','
//		<< customer << ',';
//	return ss.str();
//}

// Deserialize Customer data from a string
//Customer DeserializeCustomer(const std::string& data) {
//	std::stringstream ss(data);
//	int customerNumber, day, month, year;
//	char comma;
//	ss >> customerNumber >> comma >> day >> comma >> month >> comma >> year;
//	DateOfBirth dob(day, month, year);
//	return Customer(dob); // Assuming Customer constructor takes DateOfBirth
//}