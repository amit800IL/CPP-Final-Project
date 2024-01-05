#include "MailActions.h"

MailActionsManager::MailActionsManager()
{
	
}

//MailActionsManager::MailActionsManager(MailActionsManager&& mailActions) noexcept :
//	action(std::move(mailActions.action)) {}

void MailActionsManager::MakingAction()
{
	char input = '0';

	std::cout << "Choose which action you want to do " << std::endl;
    std::cout << "1. i want to receive a package " << std::endl;
	std::cout << "2. i want to deliever a package " << std::endl;
	std::cout << "3. i want to make a payment" << std::endl;
	std::cout << "4. i want to purchase a product " << std::endl;

	do
	{
	    std::cin >> input;

		switch (input)
		{
		   case '1':
			   std::cout << "Here is your pachage" << std::endl;
			   break;
		   case '2':
			   std::cout << "Your package has been sent" << std::endl;
			   break;
		   case '3':
			   std::cout << "Your payment has been made" << std::endl;
			   break;
		   case '4':
			   std::cout << "here is your product" << std::endl;
			   break;
		  default:
			 break;
		}

	} while (input != 'q' && input != 'Q');
	
}
MailActionsManager::~MailActionsManager() {}