/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Function.cpp holds all the information for the function declarations in the AST, including ID, filename, name, and number of parameters
 	Author: Anne Marie Bogar
 	Date: February 14, 2018
 	this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
 	Input: N/A
 	Output: N/A
*/

#include <iostream>
#include <string>
#include <vector>
#include "Function.h"
using namespace std;

//constructor -> sets filename, name, and id, sets scope as GLOBAL or MEMBER
Function::Function(string n, string i, string f, bool mem=false)
{
	name = n;
	id = i;
	file = f;
	scope = "GLOBAL";
	if(mem)
		scope = "MEMBER";
}

//returns a string of the Call in CSV form
//filename,scope,name
string Function::print()
{
	string p = file+","+scope+","+name;
	return p;
}