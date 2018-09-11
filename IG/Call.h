/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Call.h is the H file for Call.cpp, which holds all the information for the function calls in the AST, including ID, scope (the function they are found in), name, and all arguments
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
#ifndef CALL_H
#define CALL_H

class Call
{
	private:
		string scope, name, id, type;
		vector<string> args;

	public:
		Call(string s, string i, int t);
		void setName(string n);
		void addArg(string a);
		bool hasName();
		bool sameID(string i);
		void appendName(string n);
		string print();
};

#endif