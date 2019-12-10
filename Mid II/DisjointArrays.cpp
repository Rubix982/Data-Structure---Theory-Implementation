// C++ program to check if the given arrays are disjoint or not using sorting and binary search

#include<bits/stdc++.h>

using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int start, int end) {
    int x = A[end], i = (start - 1), j;

    for (j = start; j <= end - 1; j++) {
        if(A[j] <= x) {
            i++;
            swap(&A[i], &A[j]);
        }
    }

    swap (&A[i + 1], &A[end]);
    return (i + 1);
}

void quick_sort(int A[], int start, int end) {
    int pivot;
    
    if(start < end) {
    
        pivot = partition(A, start, end);
        quick_sort(A, start, pivot - 1);
        quick_sort(A, pivot + 1, end);

    }
}

int binary_search(int arr[], int low, int high, int x) {
    
    if(high >= low) {
        int mid = (low + high)/2;
        if(( mid == 0 || x > arr[mid-1]) && (arr[mid] == x)) return mid;
        else if(x > arr[mid]) return binary_search(arr, (mid + 1), high, x);
        else return binary_search(arr, low, (mid -1), x);
    }

    return -1;
}

bool isSubset(int arr1[], int arr2[],int m, int n) {
    
    quick_sort(arr1, 0, m-1);
    for ( int i = 0 ; i < n ; i++ ) 
        if ( binary_search(arr1, 0, m - 1,arr2[i]) == 1 ) 
            return false;

    return true;
}

int main() {
    
    int m,n;
    cout << "\nEnter the size of array 1 : ";
    cin >> m;
    cout << "\nEnter the size of array 2 : ";
    cin >> n;
    int arr1[m],arr2[n];
    cout << "\nEnter the array 1 elements : ";
    
    for( int i = 0 ; i < m ; i++ ) cin >> arr1[i];

    cout << "\nEnter the array 2 elements : ";
    
    for( int i = 0 ; i < n ; i++ ) cin >> arr2[i];
    
    if(isSubset(arr1, arr2, m, n)) cout << "\nThe arrays are disjoint\n ";
    else cout << "\nThe arrays are not disjoint\n";

    return 0;
}