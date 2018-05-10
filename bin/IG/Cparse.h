/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
	Cparse.h is the H file for Cparse.cpp, which processes strings found in the C/C++ Island Grammar 
		to print out a CSV with all function calls that include their ID, scope (the function they are found in), name, and all arguments
 	Author: Anne Marie Bogar
 	Date: May 9, 2018
 	this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
 	Input: N/A
 	Output: csv file
		filename(string),call_id(string),scope(string),function_name(string),argument1(string),argument2(string)...
 	for arguments, all literals are encased in <> (ex: <5>)
 	function calls that are arguments of another function call have their id next to () in csv line of the other function call
               ex: 6,GLOBAL,file.js,function1,function2()4
               **this is actually not the case right now -> just has the ID of the call
*/

#include <iostream>
#include <string>
#include <vector>
#include "Call.h"
using namespace std;
#ifndef CPARSE_H
#define CPARSE_H

class Cparse
{
	private:
		// Block struct is for classtab and functab
		struct Block{
			int indent; // indent count used to determine if in block
			string name; // for classtab only -> saves name of Class
			bool on; // set on if inside block, set off if not -> for classtab
			Block(int i, string n) : indent(i), name(n) { on = true; }
			void turnOff(){ on = false; } // set bool on to false -> for classtab
			//repurpose Block -> for classtab so that the vector is never empty
			void reinstate(int i, string n){ on = true; indent = i; name = n; }
		};
		// Argblock struct is for Mem and Arg variables in Callblock
		struct Argblock{
			int indent; // indent count used to determine if in block
			bool on; // set on if inside block, set off it not
			Argblock(){ on = false; indent = 0; } // initialize as off
			void turnOn(int i){ on = true; indent = i; } // in block -> turn on and set indent count
			void turnOff(){ on = false; indent = 0; } // not in block -> turn off
		};
		// Callblock is made for each function call and used to determine if inside block
		// each Callblock has 2 ArgBlock objects - 1 for argument blocks and 1 for member argument blocks
		struct Callblock{
			int type; // either 0 for regular or 1 for member
			int indent; // indent count used to determine if in block
			string identification; // used to find corresponding call in callList
			Argblock arg; // for argument blocks
			Argblock mem; // for member argument blocks
			bool doublemem; // turn on if double member function, e.g. obj.func1().func2()
			Callblock(int t, int i, string id) : type(t), indent(i), identification(id) { doublemem = false; }
			void turnArgOn(int i){ arg.turnOn(i); } // turn on Arg variable and set indent count -> in block
			void turnArgOff(){ arg.turnOff(); } // turn off Arg variable -> not in block
			bool argIsOn(){ return arg.on; } // returns true if Arg.on is true
			int argtab(){ return arg.indent; } // returns Arg indent count
			void turnMemOn(int i){ mem.turnOn(i); } // turn on Mem variable and set indent count -> in block
			void turnMemOff(){ mem.turnOff(); doublemem = false; } // turn off Mem variable -> not in block
			bool memIsOn(){ return mem.on; } // returns true of Mem.on is true
			int memtab(){ return mem.indent; } // returns Mem indent count
			void checkDM(){ doublemem = true; } // set doublemem to true
		};
		vector<Callblock*> calltab; //vector of Callblock pointers -> for determing if in call block
		vector<Block*> classtab; // vector of Block pointers -> for determine if in class definition block
		vector<Block*> functab; // vector of Block pointers -> for determining if in function definition block
		string sub, mem, filename;
		vector<Call*> callList; // vector of Call pointers -> keeps all Call information

	public:
		// set variables to ""
		Cparse();
		// delete all remaining allocated pointer memory
		~Cparse();
		//checks whether the AST is in an argument block or a member argument block
		bool checkarg(int tabcount, bool tick, bool memcall);
		//the AST is in an argument block
		void markarg(int tabcount);
		//the AST is in a member argument block
		void markmemarg(int tabcount);
		//checks whether a call/function/class block has finished
		void checkblock(int tabcount, bool tick);
		//checks whether the AST is inside a call block or an argument block
		bool checkcall(int tabcount, bool tick, bool memcall=false);
		// find the function call in callList that corresponds to the one in calltab
		int findCall(string i);
		//adds a new Call object to the list and a new Callblock object depending on the type of call
		void addCall(int type, int tabcount, bool tick, string id);
		//adds an argument to the last Call object in the list
		bool addArgument(int tabcount, bool tick, string a);
		//adds a BINOP or UNOP argument
		void addOp(int tabcount, bool tick, string a);
		//either saves member attribute name for later or adds member function name to latest Call object
		void addMem(int tabcount, bool tick, string attr);
		//marks argument block and signals subscript type
		void addSub(int tabcount, bool tick);
		//saves current function name
		void addFunction(int tabcount, bool tick, string f, bool memberfunc=false);
		// save the current class name
		void addClass(int tabcount, bool tick, string c);
		//adds name of the function call to the last Call object in list
		void addCallName(int tabcount, bool tick, string name);
		// add function call name to last Call object in list
		void addName(string name);
		//adds variable argument
		void addVar(int tabcount, bool tick, string a);
		// adds Class name to function (dynamic dispatch)
		void addDynamicClass(int tabcount, bool tick, string c);
		// saves filename
		void addFilename(string f);
		//any Call without a name is tagged as **Undetermined_Function**
		void cleanUp();
		//prints out the list of Calls
		void print();
		// deletes any unwanted characters in a string (specifically for commas and newlines)
		friend void editArg(string &s, string search);
};

#endif
