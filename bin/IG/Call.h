/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Call.h is the H file for Call.cpp, which holds all the information for the function calls in the AST, including ID, scope (the function they are found in), name, and all arguments
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
#ifndef CALL_H
#define CALL_H

class Call
{
	private:
		string scope, name, id, type, filename;
		vector<string> args;

	public:
		// constructor -> sets scope, id and filename, declares name as "", sets type to either MEMBER of GLOBAL
		Call(string s, string i, string f, int t);
		// sets the name of the Call
		void setName(string n);
		// adds an argument to the Call's argument vector
		void addArg(string a);
		// returns true if name is not ""
		bool hasName();
		// returns true if the ID given matches the call's id (for matching)
		bool sameID(string i);
		// add Class name to name, e.g. Class::function
		void appendName(string n);
		//returns a string of the Call in CSV form
		//filename,ID,scope,name[,arg1][,arg2][...]
		string print();
};

#endif
