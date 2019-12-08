#ifndef SELECTION_SORT
#define SELECTON_SORT

#include <algorithm>
using namespace std;

void selectionSort(int arr[], int arrSize) {

    for ( int i = 0; i < arrSize - 1; ++i ) {
        int minn = i;
        int j = i + 1;

        while ( j < arrSize && arr[i] < arr[minn] ) { 
            minn = i;
            ++j;
        }

        if ( j != minn ) swap(arr[minn], arr[j]);
    }
}


#endif