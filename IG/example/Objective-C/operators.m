#import <Foundation/Foundation.h>

void ints() {
	NSLog(@"Integers");
	int int_a = 2;
	int int_b = 5;
	
	NSLog(@"b = %d, a = %d", int_b, int_a);
	NSLog(@"\n");
	NSLog(@"b + a = %d", int_b + int_a);
	NSLog(@"b - a = %d", int_b - int_a);
	NSLog(@"a - b = %d", int_a - int_b);
	NSLog(@"b * a = %d", int_b * int_a);
	NSLog(@"b / a = %d", int_b / int_a);
	NSLog(@"b %c a = %d", '%', int_b % int_a);
	NSLog(@"\n");
	NSLog(@"\n");
}

void floats() {
	NSLog(@"Floats");
	float float_a = 2.2;
	float float_b = 5.5;
	
	NSLog(@"b = %f, a = %f", float_b, float_a);
	NSLog(@"\n");
	NSLog(@"b + a = %f", float_b + float_a);
	NSLog(@"b - a = %f", float_b - float_a);
	NSLog(@"a - b = %f", float_a - float_b);
	NSLog(@"b * a = %f", float_b * float_a);
	NSLog(@"b / a = %f", float_b / float_a);
	NSLog(@"b %c a is invalid for floats.", '%');
	NSLog(@"\n");
	NSLog(@"\n");
}

void chars() {
	NSLog(@"Chars");
	char char_a = 'a';
	char char_b = 'b';
	NSLog(@"b = '%c', a = '%c'", char_b, char_a);
	NSLog(@"\n");
	NSLog(@"b + a = %c", char_b + char_a);
	NSLog(@"b - a = %c", char_b - char_a);
	NSLog(@"a - b = %c", char_a - char_b);
	NSLog(@"b * a = %c", char_b * char_a);
	NSLog(@"b / a = %c", char_b / char_a);
	NSLog(@"b %c a = %c", '%', char_b % char_a);
	NSLog(@"\n");
	NSLog(@"\n");
}

void bools() {
	NSLog(@"Bools");
	BOOL bool_a = TRUE;
	BOOL bool_b = FALSE;
	NSLog(@"b = %d, a = %d", bool_b, bool_a);
	NSLog(@"\n");
	NSLog(@"b + a = %d", bool_b + bool_a);
	NSLog(@"b - a = %d", bool_b - bool_a);
	NSLog(@"a - b = %d", bool_a - bool_b);
	NSLog(@"b * a = %d", bool_b * bool_a);
	NSLog(@"b / a = %d", bool_b / bool_a);
	NSLog(@"b %c a is invalid for bools.", '%');
	NSLog(@"\n");
	NSLog(@"\n");
	
}

void other() {
	NSLog(@"Others");
	int int_a = 6;
	float float_a = 1.7;
	char char_a = 'a';
	BOOL bool_a = TRUE;
	
	
	NSLog(@"int_a = %d, float_a = %f, char_a = %c, bool_a = %d", int_a, float_a, char_a, bool_a );
	NSLog(@"\n");
	NSLog(@"char + bool = %c", char_a + bool_a );
	NSLog(@"float + bool = %f", float_a + bool_a );
	NSLog(@"float + char = %f", float_a + char_a );
	NSLog(@"char + int = %c", char_a + int_a );
	NSLog(@"float * char = %f", float_a * char_a );
	NSLog(@"bool / char = %c", bool_a / char_a );
	NSLog(@"float / bool = %f", float_a / bool_a );
	
}

int main() {
	ints();
	floats();
	chars();
	bools();
	other();
	
	return 0;
}









