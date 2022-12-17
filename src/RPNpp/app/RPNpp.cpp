import RPNpp.Stack;
#include <iostream>

using namespace RPNpp;


int main()
{
	Stack::Instance().push(12.3);
	std::cout << Stack::Instance().pop() << std::endl;
}
