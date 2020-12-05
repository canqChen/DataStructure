#ifndef __SortingAlgorithm__
#define __SortingAlgorithm__

// implementation of different sorting algorithm

void swap(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

/*******************************
based on comparison
*******************************/

void bubbleSort(int array[], int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				swap(array[j], array[j + 1]);
			}
		}
	}
}

void improvedBubbleSort(int array[], int length)
{
	bool flag = false;
	for (int i = 0; i < length - 1 && flag == false; i++)
	{
		flag = false;
		for (int j = 0; j < length - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				flag = true;
				swap(array[j], array[j + 1]);
			}
		}
	}
}

void selectionSort(int array[], int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		int minIdx = i;
		for (int j = i + 1; j < length; j++)
		{
			if (array[j] < array[minIdx])
			{
				minIdx = j;
			}
		}
		swap(array[i], array[minIdx]);
	}
}


int partition(int array[], int low, int high)
{
	int pivot = array[low];
	while (low < high)
	{
		while (low < high && array[high]>pivot)
			high--;
		array[low] = array[high];
		while (low < high && array[low] < pivot)
			low++;
	}
	array[low] = pivot;
	return low;
}

/* recursive quick sort  */
void quickSort(int array[], int length)
{
	
}

/*******************************
based on insertion
*******************************/

void insertionSort(int array[], int length)
{
	for (int i = 1; i < length; i++)
	{
		int j = i - 1;
		int tmp = array[i];
		while (j >= 0 && array[j] > tmp)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = tmp;
	}
}

void binaryInsertionSort(int array[], int length)
{
	for (int i = 1; i < length; i++)
	{
		int tmp = array[i];
		int low = 0, high = i - 1;

		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (array[mid] > tmp)
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (int j = i; j >= high + 2; j--)
		{
			array[j] = array[j - 1];
		}
		array[high + 1] = tmp;
	}
}

// serves for shell sort
void insertion(int array[], int gap, int idx)
{
	int tmp = array[idx];
	int j = idx - gap;
	while (j >= 0 && array[j - gap] > tmp)
	{
		array[j + gap] = array[j];
		j -= gap;
	}
	array[j + gap] = tmp;
}

void shellSort(int array[], int length)
{
	int* gaps = new int[20];
	int numGap = 0, h = 1;
	for (numGap = 0, h = 1; h < length; numGap++)
	{
		gaps[numGap] = h;
		h = 3 * h + 1;
	}

	for (numGap--; numGap >= 0; numGap--)
	{
		int gap = gaps[numGap];
		for (int i = gap; i < length; i += gap)
		{
			insertion(array, gap, i);
		}
	}
}

#endif