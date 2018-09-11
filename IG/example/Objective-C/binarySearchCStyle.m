// Dan Nelson and Nick Balsbaugh
// CS333 Programming Languages
// Project 4
// October 19, 2011
// binarySearchCStyle.m
// to run in terminal:
//   gcc binarySearchCStyle.m -o binarySearchC -framework Foundation


#import <Foundation/Foundation.h>
#import <stdlib.h>


const int LENGTH = 20;
const int NUMBER = 57;


/*
 * Sets an array of size length to random
 * values in ascending order.
 * @array: an array to fill
 * @length: the length of the array
 */
void createArray(int *array, int length);
void createArray(int *array, int length) {
	srand(time(NULL));
	int i;
	// initialize a sorted array with random values
	array[0] = 1;
	for (i=1;i<length;i++) {
		int value = rand() % 15;
		array[i] = value + array[i-1];
	}
}


/*
 * Searches array of for a target
 * @array: an array to search
 * @target: a number to search for
 * @min: the minimum index to search from
 * @max the maximum index to search to
 * @return: the index of the target or -1 if not found
 */
int recursiveBinarySearch(int *array, double target, int min, int max);
int recursiveBinarySearch(int *array, double target, int min, int max) {
	if (min > max) {
		NSLog(@"Recursively did not find %i",NUMBER);
		return -1;
	}
	
	int mid = (min + max) / 2;
	
	if (array[mid] == target) {
		NSLog(@"Recursively found %i at index %i",NUMBER,mid);
		return mid;
	}
	
	if (array[mid] < target) {
		return recursiveBinarySearch(array, target, mid+1, max);
	}
	
	return recursiveBinarySearch(array, target, min, mid-1);
}

/*
 * Searches array of for a target
 * @array: an array to search
 * @target: a number to search for
 * @length: the length of the array
 * @return: the index of the target or -1 if not found
 */
int iterativeBinarySearch(int *array, double target, int length);
int iterativeBinarySearch(int *array, double target, int length) {
	int mid;
	int min = 0;
	int max = length - 1;
	while ( min <= max )
	{
		mid = (min + max) / 2;
		if ( array[mid] == target ) {
			NSLog(@"Iteratively found %i at index %i",NUMBER,mid);
			return mid;
		}
		if ( array[mid] > target ) {
			max = mid - 1;
		}
		else {
			min = mid + 1;
		}
	}
	NSLog(@"Iteratively did not find %i",NUMBER);
	return -1;
}


/*  Main */
int main (int argc, const char * argv[]) {

	int max, min, mid;
	int value;
	int *array;

	array = malloc(sizeof(int)*LENGTH);
	createArray(array,LENGTH);

	min = 0;
	max = LENGTH-1;
		
	NSLog(@"Checking array for value %i", NUMBER);
	iterativeBinarySearch(array, NUMBER, LENGTH);
	recursiveBinarySearch(array, NUMBER, min, max);
	
	return 0;
}






