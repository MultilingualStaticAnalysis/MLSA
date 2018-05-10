/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Function.h is the H file for Function.cpp, which holds all the information for the function declarations in the AST, including ID, filename, name, and number of parameters
 	Author: Anne Marie Bogar
 	Date: May 9, 2018
 	this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
 	Input: N/A
 	Output: N/A
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef FUNCTION_H
#define FUNCTION_H

class Function
{
	private:
		string name, id, file, scope;

	public:
		//constructor -> sets filename, name, and id, sets scope as GLOBAL or MEMBER
		Function(string n, string i, string f, bool mem=false);
		//returns a string of the Call in CSV form
		string print();
};

#endif