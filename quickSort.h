#include "structs.h"

// Function to swap two pointers
void swap(gene *a, gene *b) {
    gene temp = *a;
    *a = *b;
    *b = temp;
}

// Function to run quicksort
// l is the leftmost starting index, which begins at 0
// r is the rightmost starting index, which begins at array length - 1
void quicksort(gene chromossome[], int l, int r) {
    
    if (l >= r) return;
    
    int pivot = chromossome[r].priority;
    int split = l;
    
    for (int i = l; i <= r; i++)
        if (chromossome[i].priority <= pivot) {
            swap(&chromossome[split], &chromossome[i]);
            split++;
        }
    
    quicksort(chromossome, l, split-2);
    quicksort(chromossome, split, r);
}
