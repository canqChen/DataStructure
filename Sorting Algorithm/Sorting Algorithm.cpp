// implementation of different sorting algorithm

void swap(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

void bubbleSort(int array[], int length)
{
	for (int i=0;i<length-1;i++)
	{
		for (int j=0;j<length-1-i;j++)
		{
			if (array[j] > array[j + 1])
			{
				swap(array[j], array[j + 1]);
			}
		}
	}
}

void selectionSort(int array[], int length)
{
	for (int i = 0; i < length-1; i++)
	{
		int minIdx = i;
		for (int j = i+1; j < length; j++)
		{
			if (array[j] < array[minIdx])
			{
				minIdx = j;
			}
		}
		swap(array[i], array[minIdx]);
	}
}

void insertSort(int array[], int length)
{
	for (int i = 1; i < length; i++)
	{
		int j = i - 1;
		int tmp = array[i];
		while (j>=0 && array[j]>tmp)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j+1] = tmp;
	}
}