// implementation of search algorithm


int binarySearch(int sortedArray[], int length, int key)
{
	int left = 0, right = length - 1;
	while (left<=right)
	{
		int middle = (left + right) / 2;
		if (sortedArray[middle]>key)
			right = middle - 1;
		else if (sortedArray[middle] < key)
			left = middle + 1;
		else
			return middle;
	}
	return -1;
}