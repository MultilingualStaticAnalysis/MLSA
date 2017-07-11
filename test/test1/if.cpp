#include <iostream>
#include <string>
using namespace std;
string w;
int main(){
	string v;
	int x = 5;
	int y = 1;	
	if (x > 3)
	{
		x = 4;
		v = "testing";
	}	
	else
	{
		y = 2;
	}
	while (x > 1)
	{
		y = x*y;
		x = x - 1;
	}
}
