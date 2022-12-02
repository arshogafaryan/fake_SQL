#include "fake_SQL.h"
#include <iostream>
#include <exception>

int main()
try
{
    Data d;
    parse_from_input(d);
    get_operation(d);
    return 0;
}
catch(char const* a)
{
    std::cout << a << std::endl;
}