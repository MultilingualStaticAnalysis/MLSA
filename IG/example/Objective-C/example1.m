

int foo() {
  int a = 3; // exists in this function only
  int b = 2 ;// exists in this function only
	return c + d;
}

int main (int argc, const char * argv[]) {
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

	result = foo();
	NSLog(@"a = %i", b); // illegal code
	
	[pool drain];

	return 0;
}
