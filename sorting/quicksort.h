#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <algorithm>
using namespace std;

// ! Implementation 1

// int RandomPivotPartition(int a[], int low, int high) {
//     int pvt, n, temp;
//     n = rand();

//     // Randomizing the pivot value in the given subpart of arra
//     pvt = low + n % ( high - low + 1 );

//     // Swapping pvt value from hig, so pvt value will be taken as pivot 
//     // while parititioning
//     swap(a[high], a[low]);

//     return RandomPivotPartition(a, low, high);
// }

// // Implement quicksort algorithm
// void quicksort(int a[], int low, int high) {
//     int pindex;
//     if ( low < high ) {
//         pindex = RandomPivotPartition(a, low, high);

//         // Recursively implementing quicksort
//         quicksort(a, low, pindex - 1);
//         quicksort(a, pindex + 1, high);
//     }
// }

// ! Implementation 1 end

// ! Implementation 2 start

int pivotPartition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left, j = right + 1;

    while ( true ) {
        while ( arr[++i] < pivot ) if ( i >= right ) break;
        while ( arr[--j] > pivot ) if ( j <= left ) break;

        if ( i >= j ) break;
        else swap(arr[i], arr[j]);
    }

    if ( j == left ) return j;
    swap(arr[left], arr[j]);
    return j;
}

void quicksort(int arr[], int left, int right) {
    if ( right > left ) {

        int q = pivotPartition(arr, left, right);
    
        quicksort(arr, left, q - 1);
        quicksort(arr, q + 1, right);
    }
}

#endif