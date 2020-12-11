#ifndef __SortingAlgorithm__
#define __SortingAlgorithm__

// implementation of different sorting algorithm

void swap(int& a, int& b);

/*******************************
based on comparison
*******************************/

void bubbleSort(int array[], int length);

void improvedBubbleSort(int array[], int length);

int partition(int array[], int low, int high);

/* recursive quick sort  */
void quickSort(int array[], int low, int high);

/*******************************
based on insertion
*******************************/

void insertionSort(int array[], int length);

void binaryInsertionSort(int array[], int length);

// serves for shell sort
void insertion(int array[], int gap, int idx);

void shellSort(int array[], int length);

/*******************************
based on selection
*******************************/

void selectionSort(int array[], int length);

void heapSort(int array[], int length);

void buildHeap(int array[], int length);

void adjustHeap(int array[], int root, int length);

/*******************************
merge sort
*******************************/

void mergeSort(int array[], int first, int last);

void merge(int array[], int first, int last);

/*******************************
merge sort
*******************************/

#endif