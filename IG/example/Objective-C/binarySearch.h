// Dan Nelson and Nick Balsbaugh
// CS333 Programming Languages
// Project 4
// October 19, 2011
// binarySearch.h

#import <Foundation/Foundation.h>

@interface Search: NSObject {
	NSMutableArray *_list;
	int _length;
	int _target;
	
}

-(NSMutableArray *) setList: (int) length;
-(int) setTarget: (int) target;
-(int) iterativeBinarySearch: (NSMutableArray *) list: (int) target;
-(int) recursiveBinarySearch: (NSMutableArray *) list: (int) target: (int) min: (int) max;
-(int) getLength;
-(int) getTarget;
-(void) printList;

@end