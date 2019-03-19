// BasicSortingsAndPerformanceAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
