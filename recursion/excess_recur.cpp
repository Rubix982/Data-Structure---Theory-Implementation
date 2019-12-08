#include <iostream>

int a;

int fib(int index, int a, int b) {

    int a = 0;

    if ( index == 0 )
        return a;

    fib(index - 1, b, a+b);
}

int main(void) {

    std::cout << fib(6, 0, 1) << std::endl;

    return 0;
}