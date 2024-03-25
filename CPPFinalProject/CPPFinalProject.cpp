
#include "Customer.h";
#include "CustomerQueue.h"
#include "CustomerQueueIterator.h"
#include "MailActions.h"
#include "MailCustomerCommunication.h"
#include "MailOfficial.h"
#include <iostream>

using namespace std;

int main()
{
	shared_ptr<IServiceCustomerMediator> mailActionsManager = make_shared<MailCustomerCommunication>();

	unique_ptr<MailOfficial> mailOfficial = make_unique<MailOfficial>();

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

	for (CustomerQueueIterator it = customerQueue->begin(); it != customerQueue->end(); ++it) 
	{
		Customer& customer = *it;
		mailActionsManager->CallCustomer(customer, &IServiceCustomerMediator::MakingAction);
	}

	return 0;
}

