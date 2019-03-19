

#ifndef SORTING_H
#define SORTING_H


class sorting
{
public:
	sorting();
	virtual ~sorting();
	void bubbleSort(int *arr, int sizeOfArray, int &compCount, int &moveCount);
	void quickSort(int *arr, int sizeOfArray, int &compCount, int &moveCount);
	void mergeSort(int *arr, int sizeOfArray, int &compCount, int &moveCount);
	void radixSort(int *arr, int sizeOfArray);
	void printArray(int *arr, int sizeOfArray);
	void performanceAnalysis();
protected:
private:
	void swapTwo(int *arr, int first, int second);
	void arrayPartition(int *arr, int startIndex, int endIndex, int &pivotIndex, int &compCount, int &moveCount);
	void quickSortRecursive(int *arr, int startIndex, int endIndex, int &compCount, int &moveCount);
	void mergeArrays(int *arr, int sizeOfArray, int startIndex, int mid, int endIndex, int &compCount, int &moveCount);
	void mergeSortRecursive(int *arr, int sizeOfArray, int startIndex, int endIndex, int &compCount, int &moveCount);
};

#endif // SORTING_H
