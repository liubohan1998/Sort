// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"


void QuickSort(std::vector<int>* numbers, int &SortComp, int &SortMacc) {
   QuickSortRecurse(numbers, 0, numbers->size() - 1, SortComp, SortMacc);
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int &SortComp, int &SortMacc) {
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k, SortComp, SortMacc);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   QuickSortRecurse(numbers, i, j, SortComp, SortMacc);
   QuickSortRecurse(numbers, j + 1, k, SortComp, SortMacc);
   
   return;
}

int Partition(std::vector<int>* numbers, int i, int k, int &SortComp, int &SortMacc) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = (*numbers)[midpoint];
    
    SortMacc ++;
   
   l = i;
   h = k;
   
   while (!done) {
      if((*numbers)[l] >= pivot){
          SortComp ++;
          SortMacc ++;
      }
      /* Increment l while numbers[l] < pivot */
      while ((*numbers)[l] < pivot) {
          
          SortComp ++;
          SortMacc ++;
          
         ++l;
          
          if((*numbers)[l] >= pivot){
              SortComp ++;
              SortMacc ++;
          }
      }
      
      /* Decrement h while pivot < numbers[h] */
       if(pivot >= (*numbers)[h]){
           SortComp ++;
           SortMacc ++;
       }
      while (pivot < (*numbers)[h]) {
          
          SortComp ++;
          SortMacc ++;
          
         --h;
          if(pivot >= (*numbers)[h]){
              SortComp ++;
              SortMacc ++;
          }
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = (*numbers)[l];
          SortMacc ++;
         (*numbers)[l] = (*numbers)[h];
          SortMacc += 2;
         (*numbers)[h] = temp;
          SortMacc ++;
         ++l;
         --h;
      }
   }
   
   return h;
}
