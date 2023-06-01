
#include <iostream>
#include <string>
#include "SmartStack.h"
#include "Date.h"
using std::cout;
using std::endl;
using std::string;


int main()
{
    SmartStack<Date> stack1(5);
    stack1 << Date(1,6,2023);
    stack1 << Date(31, 12, 2020);
    stack1 << Date(8, 3, 2028);
    stack1.pop().print_long();
    stack1.pop().print_long();
    stack1.pop().print_long();
}

