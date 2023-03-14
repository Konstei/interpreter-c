#include <iostream>
#include <array>
using namespace std;

/**
 * Merges two subarrays of array[].
 * First subarray is arr[begin..mid]
 * Second subarray is arr[mid+1..end]
 */
void merge(int array[], const int left, const int mid, const int right) {
	const int subArrayOne = mid - left + 1;
	const int subArrayTwo = right - mid;

	// Create temp arrays
	int *leftArray = new int[subArrayOne], *rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (int i = 0; i < subArrayOne; i++) leftArray[i] = array[left + i];
	for (int j = 0; j < subArrayTwo; j++) rightArray[j] = array[mid + 1 + j];

	int indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0, // Initial index of second sub-array
        indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		} else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

/**
 * begin is the left index
 * end is the right index
 * of the sub-array
 * of arr to be sorted
 */
void mergeSort(int array[], const int begin, const int end) {
	if (begin >= end) return; // Returns recursively

	int mid = (begin + end) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void printArray(int A[], int size) {
	for (auto i=0; i<size; i++) cout << A[i] << " ";
}

int main() {
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	auto arr_size = sizeof(arr) / sizeof(arr[0]);

	cout << "Given array is \n";
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
	return 0;
}
