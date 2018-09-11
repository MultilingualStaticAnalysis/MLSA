
// Dan Nelson and Nick Balsbaugh
// CS333 Programming Languages
// Project 4
// October 19, 2011
// binarySearch.m
// to run in terminal:
//   gcc binarySearch.m -o binarySearch -framework Foundation

#import <Foundation/Foundation.h>
#import "binarySearch.h"


const int LENGTH = 20;
const int NUMBER = 57;


// implement the Search class
@implementation Search

/*
 * Sets an NSMutableArray of size length to random
 * values in ascending order.
 * @length: the length of the array (int)
 */
-(NSMutableArray *) setList: (int) length {
	// create an array and set the first value to 1
	NSMutableArray *temp = [NSMutableArray array];
	[temp addObject: [NSNumber numberWithInteger: 1] ];
	
	int i;
	for (i=1; i<length; i++) {
		// randomly generate a number between 0 and 15
		int r = arc4random() % 15;
    	
		// get the previous number in the array
		int prev = [[temp objectAtIndex:i-1]intValue];
    	
		// add prev + r to the array
		NSNumber *num = [NSNumber numberWithInteger: prev + r];
		[temp addObject: num];
	}
    
	self->_length = [temp count];
	self->_list = temp;
	return temp;
}

/*
 * Sets an the target of the class
 * @target: the target (int)
 */
-(int) setTarget: (int) target {
    self->_target = target;
    return target;
}


/*
 * Searches a list for a target iteratively
 * @list: an NSMutableArray
 * @target: the target of the array (int)
 * @return: the index of the target if found or
 *			-1 if not found
 */
-(int) iterativeBinarySearch: (NSMutableArray *) list: (int) target {
    int mid;
	int min = 0;
	int max = self->_length - 1; // finds the length of the list
	while (min<=max) {
		mid = (min+max) / 2;
		int current = [[list objectAtIndex: mid]intValue];
		
		if ( current == target ) {
			NSLog(@"Iteratively found %i at index %i", target, mid);
			return mid;
		}
		else if ( current > target ) {
			max = mid - 1;
		}
		else {
			min = mid + 1;
		}
	}
	NSLog(@"Iteratively did not find %i", target);
	return -1;
}


/*
 * Searches a list for a target recursively
 * @list: an NSMutableArray
 * @target: the target to search for
 * @min: the minimum index to search from
 * @max: the maximum index to search to
 * @return: the index of the target if found or
 *			-1 if not found
 */
-(int) recursiveBinarySearch: (NSMutableArray *) list: (int) target: (int) min: (int) max {
	if  (min > max) {
		NSLog(@"Recursively did not find %i", target);
		return -1;
	}
	
	int mid = (min + max) / 2;
	
	int current = [[list objectAtIndex: mid]intValue];
	
	if (current == target) {
		NSLog(@"Recursively found %i at index %i", target, mid);
		return mid;
	}
	
	if (current < target) {
		return [self recursiveBinarySearch: list: target: mid+1: max];
	}
	
	return [self recursiveBinarySearch: list: target: min: mid-1];
}


/*
 * Returns the length of the list
 */
-(int) getLength {
    return self->_length;
}


/*
 * Returns the target
 */
-(int) getTarget {
    return self->_target;
}


/*
 * Prints the list of numbers
 */
-(void) printList {
	int i;
	for (i=0; i<self->_length; i++) {
    	NSLog(@"Index %2i = %3i", i, [[self->_list objectAtIndex:i]intValue]);
	}
}

@end



/* Main */
int main (int argc, const char * argv[]) {
	// to handle memory
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	// allocate a search class
	Search *search;
	search = [[Search alloc] init];
	
	// create the list of length LENGTH
	NSMutableArray *list = [search setList: LENGTH];
	
	// set the target to TARGET
	int target = [search setTarget: NUMBER];
	
	// print the list
	[search printList];
	
	// search the list
	[search recursiveBinarySearch: list: target: 0: [search getLength]-1];
	[search iterativeBinarySearch: list: target];

	// free all the memory
	[pool drain];
	return 0;
}// Dan Nels
