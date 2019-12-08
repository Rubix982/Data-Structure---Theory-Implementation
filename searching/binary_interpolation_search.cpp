#include <bits/stdc++.h>
using namespace std;

int interpolation_search(int Arr[], int low, int high, int key) {

    while ( low < high ) {

        /*

        Replace the below middle equation with the following to convert it to a Binary Search Algo
        int mid = ( low + high ) / 2;

        */

        int mid = low + ( (high - low)/(Arr[high] - Arr[low]) * ( key - Arr[low] ) );

        if ( Arr[mid] == key ) 
            return mid;
        else if ( Arr[mid] < key )
            low = mid + 1;
        else if ( Arr[mid] > key )
            high = mid - 1;
    }

    return -1;
}

int main(void) {

    int Arr[] = { 12, 15, 18, 8, 9, 25, 24, 13, 28, 19, 22, 13, 15, 8, 9, 17, 42, 32, 18, 27, 23 };

    int n = sizeof Arr/sizeof Arr[0];

    sort(Arr, Arr + n);

    std::cout << interpolation_search(Arr, 0, n, 12) << "\n";
}