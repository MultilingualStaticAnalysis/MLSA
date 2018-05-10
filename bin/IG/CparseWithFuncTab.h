/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
	Cparse.h is the H file for Cparse.cpp, which processes strings found in the C/C++ Island Grammar to print out a CSV with all function calls that include their ID, scope (the function they are found in), name, and all arguments
 	Author: Anne Marie Bogar
 	Date: February 14, 2018
 	this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
 	Input: N/A
 	Output: csv file
		call_id(string),scope(string),function_name(string),argument1(string),argument2(string)...
 	for arguments, all literals are encased in <> (ex: <5>)
 	function calls that are arguments of another function call have their id next to () in csv line of the other function call
               ex: 6,GLOBAL,file.js,function1,function2()4
*/

#include <iostream>
#include <string>
#include <vector>
#include "Call.h"
using namespace std;
#ifndef CPARSEWITHFUNCTAB_H
#define CPARSEWITHFUNCTAB_H

class Cparse
{
	private:
		struct Callblock{
			int type;
			int indent;
			string identification;
			Callblock(int t, int i, string id) : type(t), indent(i), identification(id) {}
		};
		struct Functionblock{
			int indent;
			string name;
			Functionblock(int i, string n) : indent(i), name(n) {}
		};
		vector<Callblock*> calltab;
		vector<Functionblock*> functiontab;
		int argtab, memtab;
		bool arg, memarg;
		string sub, mem, classname, filename;
		vector<Call*> callList;

	public:
		Cparse();
		~Cparse();
		bool checkarg(int tabcount, bool tick, bool memcall);
		void markarg(int tabcount);
		void markmemarg(int tabcount);
		void checkblock(int tabcount, bool tick);
		void checkfunction(int tabcount, bool tick);
		bool checkcall(int tabcount, bool tick, bool memcall=false);
		int findCall(string i);
		void addCall(int type, int tabcount, bool tick, string id);
		bool addArgument(int tabcount, bool tick, string a);
		void addOp(int tabcount, bool tick, string a);
		void addMem(int tabcount, bool tick, string attr);
		void addSub(int tabcount, bool tick);
		void addFunction(int tabcount, bool tick, string f, bool memberfunc=false);
		void addClass(int tabcount, bool tick, string c);
		void addCallName(string name);
		void addName(string name);
		void addVar(int tabcount, bool tick, string a);
		void addParmVar(int tabcount, bool tick, string a);
		void addDynamicClass(int tabcount, bool tick, string c);
		void addFilename(string f);
		void cleanUp();
		void print();
		friend void editArg(string &s, string search);
};

#endif
