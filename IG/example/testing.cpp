#include <iostream>

using namespace std;

string editArg(string s, string search, string replace, int length)
{
	std::size_t found;
	do{
		found = s.find(search);
  		if (found!=std::string::npos)
  			s.replace(found, length, replace);
  	}while(found!=std::string::npos);
  	return s;
}

int main()
{
	string a = "Hello, mister\nYay";
	a = editArg(a, "\n", "", 1);
	a = editArg(a, ",", "", 1);
	cout << a;
	return 1;
}