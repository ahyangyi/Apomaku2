#include "../alu.h"
#include <iostream>

//real_base_t<int, 32, 16> a;
float_32 a, b;

int main ()
{
    a = 3.0;
    b = 2147483648L;
    a += b;
    std::cout << a + b << std::endl;

    return 0;
}
