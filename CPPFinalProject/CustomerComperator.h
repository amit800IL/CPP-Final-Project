//#ifndef CUSTOMERCOMPERATOR_H
//#define CUSTOMERCOMPERATOR_H
//
//#include "ElderlyCustomer.h"
//#include "RegularCustomer.h"
//#include <functional>
//#include <memory>
//
//using namespace std;
//
//class CustomerComparator
//{
//public:
//	bool operator()(const std::unique_ptr<Customer>& lhs, const std::unique_ptr<Customer>& rhs) const
//	{
//		bool isLhsElderly = dynamic_cast<ElderlyCustomer*>(lhs.get()) != nullptr;
//		bool isRhsElderly = dynamic_cast<ElderlyCustomer*>(rhs.get()) != nullptr;
//
//		if (isLhsElderly && !isRhsElderly) {
//			return true;
//		}
//		else if (!isLhsElderly && isRhsElderly) {
//			return false;
//		}
//		else {
//
//			return lhs->CustomerAge() > rhs->CustomerAge();
//		}
//	}
//};
//
//#endif