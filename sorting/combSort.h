#ifndef COMBSORT_H
#define COMBSORT_H

#include <algorithm>
#include <iostream>
using namespace std;

/*
Comb Sort Algorithm
Author: Captainhampton
*/

//newGap Function
int createGap( int gap )  {
  gap = ( gap * 10 ) / 1.3;
  
  if ( gap == 9 || gap == 10 )
    gap = 11;
  
  if (gap < 1)
    gap = 1;
  
  return gap;
} //end newGap Function

void combSort(int data[], int size) {
  int gap = size;
  
  while(true) {
   	  gap = createGap( gap );
	  bool swapped = false;
    
	for (int i = 0; i < size - gap; i++) {
      int j = i + gap;

      if ( data[i] > data[j] ){
        swap(data[i], data[j]);
        swapped = true;
      } // end if
    
	} // end for
    
	if (gap == 1 && !swapped)
      break;
    } // end for
} // end combSort Function

#endif