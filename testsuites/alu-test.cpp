#include "../alu.h"
#include <iostream>

typedef real<1023> the_float;
the_float a, b;

int main ()
{
    a = 3.0;
    b = 2147483648L;
    a += b;
    std::cout << a + b << std::endl;

    return 0;
}
