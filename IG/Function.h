/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Function.h is the H file for Function.cpp, which holds all the information for the function declarations in the AST, including ID, filename, name, and number of parameters
 	Author: Anne Marie Bogar
 	Date: February 14, 2018
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
		string name, id, file, infiniteParams, scope;
		int params;

	public:
		Function(string n, string i, string f, int p, bool inf, bool mem=false);
		string print();
};

#endif