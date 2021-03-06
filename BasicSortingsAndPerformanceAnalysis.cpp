#include "pch.h"
#include <iostream>
#include "sorting.h"

using namespace std;

int main()
{
	char end;

	sorting sortObject;
	int arr[16] = { 7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5 };
	int compCount = 0;
	int moveCount = 0;

	sortObject.bubbleSort(arr, 16, compCount, moveCount);
	sortObject.printArray(arr, 16);
	cout << endl;
	sortObject.quickSort(arr, 16, compCount, moveCount);
	sortObject.printArray(arr, 16);
	cout << endl;
	sortObject.mergeSort(arr, 16, compCount, moveCount);
	sortObject.printArray(arr, 16);
	cout << endl;
	sortObject.radixSort(arr, 16);
	sortObject.printArray(arr, 16);
	cout << endl;
	sortObject.performanceAnalysis();

	cin >> end;
	return 0;
}
