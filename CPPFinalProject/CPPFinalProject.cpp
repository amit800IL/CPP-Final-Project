
#include "PostOffice.h"

using namespace std;

int main()
{
	unique_ptr<PostOffice> postOffice = make_unique<PostOffice>();
	return 0;
}

