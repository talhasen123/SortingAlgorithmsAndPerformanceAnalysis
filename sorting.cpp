#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "time.h"
#include "sorting.h"

using namespace std;

sorting::sorting() {}

sorting::~sorting() {}

/**
* This function swaps two numbers in an array.
**/
void sorting::swapTwo(int *arr, int first, int second)
{
	int temp;
	temp = arr[first]; // Get the first element in a temp slot.
	arr[first] = arr[second]; // Put the second value in the first index.
	arr[second] = temp; // Put the first value in the second index.
}

/**
* This function sorts an array with the Bubble Sort algorithm. Its worst case time complexity is O(n^2).
**/
void sorting::bubbleSort(int *arr, int sizeOfArray, int &compCount, int &moveCount)
{
	// Initialize comparison and move values to 0.
	compCount = 0;
	moveCount = 0;
	int tempSize = sizeOfArray;

	// Traverse the whole unsorted array, each time you encounter a pair which aren't sorted, swap them. Do this until every element is sorted.
	for (int i = 0; i + 1 < sizeOfArray; i++)
	{
		for (int p = 0; p + 1 < tempSize; p++)
		{
			compCount++; // Comparison done.
			if (arr[p] > arr[p + 1])
			{
				swapTwo(arr, p, p + 1);
				moveCount += 3; // 3 assignments done for a swap.
			}
		}
		tempSize--; // Decrease the unsorted part by 1.
	}
}

/**
* This functions sorts an array with the Quick Sort algorithm. Its worst case time complexity is O(n^2) but its average case is O(n*log(n)).
**/

/**
* This functions partitions an array into 2 parts, one part is bigger than the pivot number and the other part is smaller. Pivot is chosen as the first index of the array.
* Pivot is then placed in the middle of these 2 parts.
**/
void sorting::arrayPartition(int *arr, int startIndex, int endIndex, int &pivotIndex, int &compCount, int &moveCount)
{
	int pivot = arr[startIndex]; // Make the first element pivot.
	moveCount++; // Assignment.
	int lastLessPivot = startIndex; // Initialize the index for numbers which are less than the pivot.

	for (int firstUnknown = startIndex + 1; firstUnknown <= endIndex; firstUnknown++)
	{
		compCount++; // Comparison done.
		if (arr[firstUnknown] < pivot)
		{
			lastLessPivot++; // Increase the index for numbers which are less than the pivot by 1.
			swapTwo(arr, lastLessPivot, firstUnknown); // Put the unknown number in the less than pivot part.
			moveCount += 3; // Swap is 3 assignments.
		}
		// else the number is bigger than the pivot, in that case just move the unknown pointer.
	}
	swapTwo(arr, startIndex, lastLessPivot); // Move the pivot to the middle.
	moveCount += 3; // Swap is 3 assignments.
	pivotIndex = lastLessPivot; // Pivot index is in the middle.
}

/**
* This function recursively sorts the array with Quick Sort.
**/
void sorting::quickSortRecursive(int *arr, int startIndex, int endIndex, int &compCount, int &moveCount)
{
	int pivotIndex; // Stores the pivot index.

	if (startIndex < endIndex) // Base condition.
	{
		arrayPartition(arr, startIndex, endIndex, pivotIndex, compCount, moveCount); // Partition array into 2 parts corresponding to the pivot.

		quickSortRecursive(arr, startIndex, pivotIndex - 1, compCount, moveCount); // quick sort the first part.
		quickSortRecursive(arr, pivotIndex + 1, endIndex, compCount, moveCount); // quick sort the second part.
	}
}

/**
* This is the function user calls for sorting the array with Quick Sort.
**/
void sorting::quickSort(int *arr, int sizeOfArray, int &compCount, int &moveCount)
{
	compCount = 0;
	moveCount = 0;

	quickSortRecursive(arr, 0, sizeOfArray - 1, compCount, moveCount); // Calls quick sort to whole array.
}

/**
* These functions sorts an array with the Merge Sort algorithm. Its worst case time complexity is O(n*log(n)).
**/

/**
* This functions merges 2 arrays into one single array, each element is placed into their corresponding sorted place in the final array.
**/
void sorting::mergeArrays(int *arr, int sizeOfArray, int startIndex, int mid, int endIndex, int &compCount, int &moveCount)
{
	int* tempArray = new int[sizeOfArray]; // Stores the sorted array in a temp array.

	int firstHalfF = startIndex; // First half's first index.
	int firstHalfL = mid; // First half's last index which is middle.
	int secondHalfF = mid + 1; // Second half's first index.
	int secondHalfL = endIndex; // Second half's last index.
	int i = startIndex; // Loop counter which is the start.

	while ((firstHalfF <= firstHalfL) && (secondHalfF <= secondHalfL)) // If first or second half is not wholly finished, compare the members and put them in the temp array.
	{
		compCount++;
		if (arr[firstHalfF] < arr[secondHalfF]) // Compare the elements in first and second half, put the smallest one to the sorted temp array and move that half by 1 if first is smaller.
		{
			tempArray[i] = arr[firstHalfF];
			firstHalfF++;
			moveCount++;
		}
		else // Else put the one in the second half and move it by 1.
		{
			tempArray[i] = arr[secondHalfF];
			secondHalfF++;
			moveCount++;
		}
		i++;
	}

	while (firstHalfF <= firstHalfL) // If there are remaining elements in the first half, put them in the temp array accordingly.
	{
		tempArray[i] = arr[firstHalfF];
		moveCount++;
		firstHalfF++;
		i++;
	}

	while (secondHalfF <= secondHalfL) // If there are remaining elements in the second half, put them in the temp array accordingly.
	{
		tempArray[i] = arr[secondHalfF];
		moveCount++;
		secondHalfF++;
		i++;
	}

	for (int p = startIndex; p <= endIndex; p++) // Copy the temp array to the original array. This means merge sort is not in-place algorithm.
	{
		arr[p] = tempArray[p];
		moveCount++;
	}

	delete tempArray;
}

/**
* This function recursively sorts the array with Merge Sort.
**/
void sorting::mergeSortRecursive(int *arr, int sizeOfArray, int startIndex, int endIndex, int &compCount, int &moveCount)
{
	if (startIndex < endIndex) // Base condition.
	{
		int mid = (endIndex + startIndex) / 2; // Cut the array in half.

		mergeSortRecursive(arr, sizeOfArray, startIndex, mid, compCount, moveCount); // merge sort the first half recursively.
		mergeSortRecursive(arr, sizeOfArray, mid + 1, endIndex, compCount, moveCount);  // merge sort the second half recursively.

		mergeArrays(arr, sizeOfArray, startIndex, mid, endIndex, compCount, moveCount); // Merge the recursively sorted half.
	}
}

/**
* This is the function user calls for sorting the array with Merge Sort.
**/
void sorting::mergeSort(int *arr, int sizeOfArray, int &compCount, int &moveCount)
{
	compCount = 0;
	moveCount = 0;

	mergeSortRecursive(arr, sizeOfArray, 0, sizeOfArray - 1, compCount, moveCount); // Merge sorts the whole array.
}

/**
* This functions sorts an array with the Radix Sort algorithm. Its worst case time complexity is O(n) (approximately).
**/
void sorting::radixSort(int *arr, int sizeOfArray)
{
	int** tempArray = new int*[10]; // This temporary array holds the 10 buckets (for base 10). Each digit corresponds to 1 bucket and each bucket can have every element of the original array.
	for (int h = 0; h < 10; h++)
	{
		tempArray[h] = new int[sizeOfArray];
	}
	int counter[10] = { 0 }; // This array holds counters for each bucket.
	int counted; // This integer is used for replacing each element in the array with the elements in the buckets. It is a loop counter.
	int arrayElementDigit; // This is the current right-most significant digit of an array element.

	// This is the radix sort for each digit. It is assumed there are max 5 digits because in fact in the performanceAnalysis function the random number range is [1,10000],
	// meaning max digit can at most be 5.
	for (int i = 5; i > 0; i--)
	{

		for (int n = 0; n < 10; n++)
		{
			counter[n] = 0; // Initializing each counter to 0.
		}
		for (int t = 0; t < sizeOfArray; t++)
		{
			arrayElementDigit = arr[t]; // Getting the current array element.
			for (int p = i; p < 5; p++)
			{
				arrayElementDigit /= 10; // Go to the corresponding digit.
			}
			arrayElementDigit %= 10; // Get the digit.
			tempArray[arrayElementDigit][counter[arrayElementDigit]] = arr[t]; // Put the current array element to its corresponding digit bucket and its index.
			counter[arrayElementDigit]++; // Increase the counter for that digit bucket by 1 (because a number was added).
		}
		counted = 0; // Index counter for the array elements.

		// This is the replacement loop for the array with bucket elements. It is done 10 times (for 10 digits).
		for (int q = 0; q < 10; q++)
		{
			// Replacing each element with the elements in the buckets, starting from the 0 bucket. Loop stop condition is the size of the bucket (its counter).
			for (int k = 0; k < counter[q]; k++)
			{
				arr[counted] = tempArray[q][k]; // Replace the current array element with the corresponding bucket and its corresponding index.
				++counted; // Go to the next array element.
			}
		}
	}
	for (int q = 0; q < 10; q++)
	{
		delete tempArray[q];
	}
	delete tempArray;
}

/**
* This function prints all elements of an array.
**/
void sorting::printArray(int *arr, int sizeOfArray)
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		cout << arr[i] << " ";
	}
}

/**
* This function tests all 4 sorting algorithms with varying array inputs. It calculates their running time, comparison amounts and assignments amounts.
* After that, it prints a result table containing all the information.
**/
void sorting::performanceAnalysis()
{
	int compCountBubble;
	int compCountQuick;
	int compCountMerge;
	int moveCountBubble;
	int moveCountQuick;
	int moveCountMerge;

	/**
	*****************************************************************************************************************************************
	* This part until the end creates a dynamic 3D result array which holds the tests, sorting algorithms and their results.
	* First layer holds the 8 different test amounts (array sizes).
	* Second layer holds the 4 different sorting algorithms.
	* Third layer holds the 3 different result types (comparisons, move amounts and elapsed time).
	* In the start of every test, corresponding 4 dynamic arrays are initialized with the proper sizes.
	* And each array is filled with the same random number in the same index (so all arrays are the same).
	* Random number range is [1, 10000].
	* Then these arrays are sorted corresponding to their sorting algorithms, their results are recorded and stored.
	* But reminder that only elapsed time is recorded for radix sort. Comparison and move amounts are not recorded for this sorting algorithm.
	* After 8 tests are done, results are printed out like the one given as an example, all arrays are deleted including the 3D result array.
	* IMPORTANT: FOR ELAPSED TIMES SMALLER THAN 1 MILISECOND, IT IS RECORDED AS 1 MILISECOND BECAUSE RESULTS ARE HOLD WITH 3 SIGNIFICANT DIGITS.
	* THIS IS ESPECIALLY DONE FOR RADIX AND MERGE SORTS. THEIR RESULTS WERE HOLD AS '0' IN SYSTEM BEFORE SO THIS CHANGE WAS DONE.
	*****************************************************************************************************************************************
	*/

	double ***result = new double**[8];
	for (int p = 0; p < 8; p++)
	{
		result[p] = new double*[4];
		for (int t = 0; t < 4; t++)
		{
			result[p][t] = new double[3];
		}
	}

	int *bubbleArray1 = new int[2000];
	int *quickArray1 = new int[2000];
	int *mergeArray1 = new int[2000];
	int *radixArray1 = new int[2000];

	for (int i = 0; i < 2000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray1[i] = temp;
		quickArray1[i] = temp;
		mergeArray1[i] = temp;
		radixArray1[i] = temp;
	}

	clock_t tStart = clock();
	bubbleSort(bubbleArray1, 2000, compCountBubble, moveCountBubble);
	result[0][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[0][0][1] = (double)compCountBubble;
	result[0][0][2] = (double)moveCountBubble;

	tStart = clock();
	quickSort(quickArray1, 2000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[0][1][0] = 0.01;
	}
	else {
		result[0][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[0][1][1] = (double)compCountQuick;
	result[0][1][2] = (double)moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray1, 2000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[0][2][0] = 0.01;
	}
	else {
		result[0][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[0][2][1] = (double)compCountMerge;
	result[0][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray1, 2000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[0][3][0] = 0.01;
	}
	else {
		result[0][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray1;
	delete quickArray1;
	delete mergeArray1;
	delete radixArray1;

	int *bubbleArray2 = new int[6000];
	int *quickArray2 = new int[6000];
	int *mergeArray2 = new int[6000];
	int *radixArray2 = new int[6000];

	for (int i = 0; i < 6000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray2[i] = temp;
		quickArray2[i] = temp;
		mergeArray2[i] = temp;
		radixArray2[i] = temp;
	}

	tStart = clock();
	bubbleSort(bubbleArray2, 6000, compCountBubble, moveCountBubble);
	result[1][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[1][0][1] = (double)compCountBubble;
	result[1][0][2] = (double)moveCountBubble;

	tStart = clock();
	quickSort(quickArray2, 6000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[1][1][0] = 0.01;
	}
	else {
		result[1][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[1][1][1] = (double)compCountQuick;
	result[1][1][2] = (double)moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray2, 6000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[1][2][0] = 0.01;
	}
	else {
		result[1][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[1][2][1] = (double)compCountMerge;
	result[1][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray2, 6000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[1][3][0] = 0.01;
	}
	else {
		result[1][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray2;
	delete quickArray2;
	delete mergeArray2;
	delete radixArray2;


	int *bubbleArray3 = new int[10000];
	int *quickArray3 = new int[10000];
	int *mergeArray3 = new int[10000];
	int *radixArray3 = new int[10000];

	for (int i = 0; i < 10000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray3[i] = temp;
		quickArray3[i] = temp;
		mergeArray3[i] = temp;
		radixArray3[i] = temp;
	}

	tStart = clock();
	bubbleSort(bubbleArray3, 10000, compCountBubble, moveCountBubble);
	result[2][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[2][0][1] = (double)compCountBubble;
	result[2][0][2] = (double)moveCountBubble;

	tStart = clock();
	quickSort(quickArray3, 10000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[2][1][0] = 0.01;
	}
	else {
		result[2][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[2][1][1] = compCountQuick;
	result[2][1][2] = moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray3, 10000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[2][2][0] = 0.01;
	}
	else {
		result[2][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[2][2][1] = (double)compCountMerge;
	result[2][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray3, 10000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[2][3][0] = 0.01;
	}
	else {
		result[2][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray3;
	delete quickArray3;
	delete mergeArray3;
	delete radixArray3;


	int *bubbleArray4 = new int[14000];
	int *quickArray4 = new int[14000];
	int *mergeArray4 = new int[14000];
	int *radixArray4 = new int[14000];

	for (int i = 0; i < 14000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray4[i] = temp;
		quickArray4[i] = temp;
		mergeArray4[i] = temp;
		radixArray4[i] = temp;
	}

	tStart = clock();
	bubbleSort(bubbleArray4, 14000, compCountBubble, moveCountBubble);
	result[3][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[3][0][1] = (double)compCountBubble;
	result[3][0][2] = (double)moveCountBubble;

	tStart = clock();
	quickSort(quickArray4, 14000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[3][1][0] = 0.01;
	}
	else {
		result[3][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[3][1][1] = (double)compCountQuick;
	result[3][1][2] = (double)moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray4, 14000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[3][2][0] = 0.01;
	}
	else {
		result[3][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[3][2][1] = (double)compCountMerge;
	result[3][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray4, 14000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[3][3][0] = 0.01;
	}
	else {
		result[3][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray4;
	delete quickArray4;
	delete mergeArray4;
	delete radixArray4;


	int *bubbleArray5 = new int[18000];
	int *quickArray5 = new int[18000];
	int *mergeArray5 = new int[18000];
	int *radixArray5 = new int[18000];

	for (int i = 0; i < 18000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray5[i] = temp;
		quickArray5[i] = temp;
		mergeArray5[i] = temp;
		radixArray5[i] = temp;
	}

	tStart = clock();
	bubbleSort(bubbleArray5, 18000, compCountBubble, moveCountBubble);
	result[4][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[4][0][1] = compCountBubble;
	result[4][0][2] = moveCountBubble;

	tStart = clock();
	quickSort(quickArray5, 18000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[4][1][0] = 0.01;
	}
	else {
		result[4][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[4][1][1] = (double)compCountQuick;
	result[4][1][2] = (double)moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray5, 18000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[4][2][0] = 0.01;
	}
	else {
		result[4][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[4][2][1] = (double)compCountMerge;
	result[4][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray5, 18000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[4][3][0] = 0.01;
	}
	else {
		result[4][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray5;
	delete quickArray5;
	delete mergeArray5;
	delete radixArray5;

	int *bubbleArray6 = new int[22000];
	int *quickArray6 = new int[22000];
	int *mergeArray6 = new int[22000];
	int *radixArray6 = new int[22000];

	for (int i = 0; i < 22000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray6[i] = temp;
		quickArray6[i] = temp;
		mergeArray6[i] = temp;
		radixArray6[i] = temp;
	}

	tStart = clock();
	bubbleSort(bubbleArray6, 22000, compCountBubble, moveCountBubble);
	result[5][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[5][0][1] = (double)compCountBubble;
	result[5][0][2] = (double)moveCountBubble;

	tStart = clock();
	quickSort(quickArray6, 22000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[5][1][0] = 0.01;
	}
	else {
		result[5][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[5][1][1] = (double)compCountQuick;
	result[5][1][2] = (double)moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray6, 22000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[5][2][0] = 0.01;
	}
	else {
		result[5][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[5][2][1] = (double)compCountMerge;
	result[5][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray6, 22000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[5][3][0] = 0.01;
	}
	else {
		result[5][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray6;
	delete quickArray6;
	delete mergeArray6;
	delete radixArray6;


	int *bubbleArray7 = new int[26000];
	int *quickArray7 = new int[26000];
	int *mergeArray7 = new int[26000];
	int *radixArray7 = new int[26000];

	for (int i = 0; i < 26000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray7[i] = temp;
		quickArray7[i] = temp;
		mergeArray7[i] = temp;
		radixArray7[i] = temp;
	}

	tStart = clock();
	bubbleSort(bubbleArray7, 26000, compCountBubble, moveCountBubble);
	result[6][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[6][0][1] = (double)compCountBubble;
	result[6][0][2] = (double)moveCountBubble;

	tStart = clock();
	quickSort(quickArray7, 26000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[6][1][0] = 0.01;
	}
	else {
		result[6][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[6][1][1] = (double)compCountQuick;
	result[6][1][2] = (double)moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray7, 26000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[6][2][0] = 0.01;
	}
	else {
		result[6][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[6][2][1] = (double)compCountMerge;
	result[6][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray7, 26000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[6][3][0] = 0.01;
	}
	else {
		result[6][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray7;
	delete quickArray7;
	delete mergeArray7;
	delete radixArray7;


	int *bubbleArray8 = new int[30000];
	int *quickArray8 = new int[30000];
	int *mergeArray8 = new int[30000];
	int *radixArray8 = new int[30000];

	for (int i = 0; i < 30000; i++)
	{
		int temp = rand() % 10000 + 1;
		bubbleArray8[i] = temp;
		quickArray8[i] = temp;
		mergeArray8[i] = temp;
		radixArray8[i] = temp;
	}

	tStart = clock();
	bubbleSort(bubbleArray8, 30000, compCountBubble, moveCountBubble);
	result[7][0][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	result[7][0][1] = (double)compCountBubble;
	result[7][0][2] = (double)moveCountBubble;

	tStart = clock();
	quickSort(quickArray8, 30000, compCountQuick, moveCountQuick);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[7][1][0] = 0.01;
	}
	else {
		result[7][1][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[7][1][1] = (double)compCountQuick;
	result[7][1][2] = (double)moveCountQuick;

	tStart = clock();
	mergeSort(mergeArray8, 30000, compCountMerge, moveCountMerge);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[7][2][0] = 0.01;
	}
	else {
		result[7][2][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}
	result[7][2][1] = (double)compCountMerge;
	result[7][2][2] = (double)moveCountMerge;

	tStart = clock();
	radixSort(radixArray8, 30000);
	if ((double)(clock() - tStart) / CLOCKS_PER_SEC == 0)
	{
		result[7][3][0] = 0.01;
	}
	else {
		result[7][3][0] = (double)(clock() - tStart) / CLOCKS_PER_SEC;
	}

	delete bubbleArray8;
	delete quickArray8;
	delete mergeArray8;
	delete radixArray8;

	/**
	* Results are printed like the one given as an example.
	* Results are printed like a matrix.
	* Rows are the test sizes and columns are the corresponding result types.
	* Each sorting algorithm's results are printed seperately.
	*/
	cout << "---------------------------------------------------------" << endl;
	cout << "Part c - Time analysis of Bubble Sort" << endl;
	cout << "Array Size\tTime Elapsed\tcompCount\tmoveCount" << endl;
	cout << "2000\t\t" << result[0][0][0] << "\t\t" << result[0][0][1] << "\t" << result[0][0][2] << endl;
	cout << "6000\t\t" << result[1][0][0] << "\t\t" << result[1][0][1] << "\t" << result[1][0][2] << endl;
	cout << "10000\t\t" << result[2][0][0] << "\t\t" << result[2][0][1] << "\t" << result[2][0][2] << endl;
	cout << "14000\t\t" << result[3][0][0] << "\t\t" << result[3][0][1] << "\t" << result[3][0][2] << endl;
	cout << "18000\t\t" << result[4][0][0] << "\t\t" << result[4][0][1] << "\t" << result[4][0][2] << endl;
	cout << "22000\t\t" << result[5][0][0] << "\t\t" << result[5][0][1] << "\t" << result[5][0][2] << endl;
	cout << "26000\t\t" << result[6][0][0] << "\t\t" << result[6][0][1] << "\t" << result[6][0][2] << endl;
	cout << "30000\t\t" << result[7][0][0] << "\t\t" << result[7][0][1] << "\t" << result[7][0][2] << endl;
	cout << "---------------------------------------------------------" << endl;

	cout << "---------------------------------------------------------" << endl;
	cout << "Part c - Time analysis of Quick Sort" << endl;
	cout << "Array Size\tTime Elapsed\tcompCount\tmoveCount" << endl;
	cout << "2000\t\t" << result[0][1][0] << "\t\t" << result[0][1][1] << "\t\t" << result[0][1][2] << endl;
	cout << "6000\t\t" << result[1][1][0] << "\t\t" << result[1][1][1] << "\t\t" << result[1][1][2] << endl;
	cout << "10000\t\t" << result[2][1][0] << "\t\t" << result[2][1][1] << "\t\t" << result[2][1][2] << endl;
	cout << "14000\t\t" << result[3][1][0] << "\t\t" << result[3][1][1] << "\t\t" << result[3][1][2] << endl;
	cout << "18000\t\t" << result[4][1][0] << "\t\t" << result[4][1][1] << "\t\t" << result[4][1][2] << endl;
	cout << "22000\t\t" << result[5][1][0] << "\t\t" << result[5][1][1] << "\t\t" << result[5][1][2] << endl;
	cout << "26000\t\t" << result[6][1][0] << "\t\t" << result[6][1][1] << "\t\t" << result[6][1][2] << endl;
	cout << "30000\t\t" << result[7][1][0] << "\t\t" << result[7][1][1] << "\t\t" << result[7][1][2] << endl;
	cout << "---------------------------------------------------------" << endl;

	cout << "---------------------------------------------------------" << endl;
	cout << "Part c - Time analysis of Merge Sort" << endl;
	cout << "Array Size\tTime Elapsed\tcompCount\tmoveCount" << endl;
	cout << "2000\t\t" << result[0][2][0] << "\t\t" << result[0][2][1] << "\t\t" << result[0][2][2] << endl;
	cout << "6000\t\t" << result[1][2][0] << "\t\t" << result[1][2][1] << "\t\t" << result[1][2][2] << endl;
	cout << "10000\t\t" << result[2][2][0] << "\t\t" << result[2][2][1] << "\t\t" << result[2][2][2] << endl;
	cout << "14000\t\t" << result[3][2][0] << "\t\t" << result[3][2][1] << "\t\t" << result[3][2][2] << endl;
	cout << "18000\t\t" << result[4][2][0] << "\t\t" << result[4][2][1] << "\t\t" << result[4][2][2] << endl;
	cout << "22000\t\t" << result[5][2][0] << "\t\t" << result[5][2][1] << "\t\t" << result[5][2][2] << endl;
	cout << "26000\t\t" << result[6][2][0] << "\t\t" << result[6][2][1] << "\t\t" << result[6][2][2] << endl;
	cout << "30000\t\t" << result[7][2][0] << "\t\t" << result[7][2][1] << "\t\t" << result[7][2][2] << endl;
	cout << "---------------------------------------------------------" << endl;

	cout << "---------------------------------------------------------" << endl;
	cout << "Part c - Time analysis of Radix Sort" << endl;
	cout << "Array Size\tTime Elapsed" << endl;
	cout << "2000\t\t" << result[0][3][0] << endl;
	cout << "6000\t\t" << result[1][3][0] << endl;
	cout << "10000\t\t" << result[2][3][0] << endl;
	cout << "14000\t\t" << result[3][3][0] << endl;
	cout << "18000\t\t" << result[4][3][0] << endl;
	cout << "22000\t\t" << result[5][3][0] << endl;
	cout << "26000\t\t" << result[6][3][0] << endl;
	cout << "30000\t\t" << result[7][3][0] << endl;
	cout << "---------------------------------------------------------" << endl;

	// Deleting all the 3D result array.
	for (int j = 0; j < 8; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			delete result[j][k];
		}
		delete result[j];
	}
	delete result;
}

