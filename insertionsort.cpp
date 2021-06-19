// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"

void InsertionSort(std::vector<int>* numbers, int &SortComp, int &SortMacc) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
       if((*numbers)[j] >= (*numbers)[j - 1]){
           SortComp ++;
           SortMacc += 2;
       }
       while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
           SortComp++;
           SortMacc += 2;
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
           SortMacc++;
         (*numbers)[j] = (*numbers)[j - 1];
           SortMacc += 2;
         (*numbers)[j - 1] = temp;
           SortMacc ++;
         --j;
        if(j > 0 && (*numbers)[j] >= (*numbers)[j - 1]){
               SortComp++;
            SortMacc += 2;
        }
        
      }
   }
}
