#include <iostream>
using namespace std;

int factorial(int iter, int prod = 1) {
    if ( iter == 0 )
        return prod;
    
    // This also works
    // return factorial( iter - 1, prod * iter);
    factorial( iter - 1, prod * iter);
}

int main(void) {
    
    cout << factorial(5) << endl;

    return 0;
}