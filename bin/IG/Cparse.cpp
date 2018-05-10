/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Cparse.cpp processes strings found in the C/C++ Island Grammar to print out a CSV with all function calls that include their ID, scope (the function they are found in), name, and all arguments
 	Author: Anne Marie Bogar
 	Date: May 9, 2018
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
#include <typeinfo>
#include <vector>
#include <algorithm>
#include <cctype>
#include "Cparse.h"
#include "Call.h"
using namespace std;

//default constructor -> set starting values for member variables
Cparse::Cparse()
{
	sub = "";
	mem = "";
	filename = "initialized";
}

//destructor -> delete all Call, Callblock, and Block pointers
Cparse::~Cparse()
{
	for(int k=0; k<callList.size(); k++){
		delete callList[k];
	}
	for(int j=0; j<calltab.size(); j++){
		delete calltab[j];
	}
	for(int m=0; m<classtab.size(); m++){
		delete classtab[m];
	}
	for(int i=0; i<functab.size(); i++){
		delete functab[i];
	}
}

//checks whether the AST is in an argument block or a member argument block
//if in block, do not add argument unless it is the name of a subscript variable
bool Cparse::checkarg(int tabcount, bool tick, bool memcall)
{
	if(calltab.back()->argIsOn()){
		//checks whether the argument block has finished
		if((calltab.back()->argtab() > tabcount)||((calltab.back()->argtab() == tabcount)&&(!tick))){
			// block has finished -> turn off Arg variable and set mem to ""
			calltab.back()->turnArgOff();
			mem = "";
			return true; // not on block -> can add argument
		} else if(sub == "[]"){
			return true; // add name of subscript
		} else if(memcall && !calltab.back()->memIsOn()){
			return true; // add Class name
		} else {
			return false; // in block -> cannot add argument
		}
	}
	if(calltab.back()->memIsOn()){
		//checks whether the member argument block has finished
		if((calltab.back()->memtab() > tabcount)||((calltab.back()->memtab() == tabcount)&&(!tick))){
			// block has finished -> turn off Mem variable and set mem to ""
			calltab.back()->turnMemOff();
			mem = "";
			return true; // not in block -> can add argument
		} else {
			return false; // in block -> cannot add argument
		}
	}
	return true; // not in block -> can add argument
}

//the AST is in an argument block
void Cparse::markarg(int tabcount)
{
	// turn on Arg argument and set indent count
	calltab.back()->turnArgOn(tabcount);
}

//the AST is in a member argument block
void Cparse::markmemarg(int tabcount)
{
	// turn on Mem argument and set indent count
	calltab.back()->turnMemOn(tabcount);
}

//checks whether a call block has finished
//if the indent is smaller than or equal to the call indent and there is no tick, the call block has finished
void Cparse::checkblock(int tabcount, bool tick)
{
	//call block
	int tabs = calltab.size();
	for(int k = 0; k < tabs; k++){
		if((calltab.back()->indent > tabcount)||((calltab.back()->indent == tabcount)&&(!tick))){
			// not in block -> delete last Callblock object (dynamically allocated) and pop off vector
			delete calltab.back();
			calltab.pop_back();
		}
	}
	//class block - make sure there is a class at all times
	int ctabs = classtab.size();
	for(int k = 0; k < ctabs; k++){
		if((classtab.back()->indent > tabcount)||((classtab.back()->indent == tabcount)&&(!tick))){
			if(classtab.size() == 1)
				// make sure that at least one Block object is always in the list
				// turn off on variable to signify that Class definition is done
				classtab.back()->turnOff();
			else{
				// not in block -> delete last Block object (dynamically allocated) and pop off vector
				delete classtab.back();
				classtab.pop_back();
			}
		}
	}
	//function block
	int ftabs = functab.size();
	for(int k = 0; k < ftabs; k++){
		if((functab.back()->indent > tabcount)||((functab.back()->indent == tabcount)&&(!tick))){
			// not in block -> delete last Block object (dynamically allocated) and pop off vector
			delete functab.back();
			functab.pop_back();
		}
	}
}

//checks whether the AST is inside a call block or an argument block
bool Cparse::checkcall(int tabcount, bool tick, bool memcall=false)
{
	checkblock(tabcount, tick); // check that inside Call/Class/Function block
	if(calltab.empty()){
		// made sure mem variable is set to ""
		mem = "";
		return false; // not in function call block -> do not add argument
	} else {
		return checkarg(tabcount, tick, memcall); // in call block -> check Arg and Mem before adding argument
	}
}

// find the function call in callList that corresponds to the one in calltab
int Cparse::findCall(string i)
{
	for(int k=0; k<callList.size(); k++){
		if(callList[k]->sameID(i))
			return k;
	}
	return -1; // if call cannot be found, return -1
}

//adds a new Call object to the list and a new Callblock object depending on the type of call
void Cparse::addCall(int type, int tabcount, bool tick, string id)
{
	checkcall(tabcount, tick); // check that inside Call/Class/Function block
	if(!calltab.empty()){
		// check if member function call, and inside Mem block
		if(type && calltab.back()->memIsOn()){
			// set mem to "" to start over for new Call object
			mem = "";
		} else {
			// if not in Arg block, add call as an argument to previous function call
			if(!calltab.back()->argIsOn()){
				int k = findCall(calltab.back()->identification);
				if(k != -1)
					callList[k]->addArg(id);
			}
		}
	}
	calltab.push_back(new Callblock(type, tabcount, id)); // add new function call to tabcount
	if(!functab.empty())
		callList.push_back(new Call(functab.back()->name, id, filename, type)); // add new call to callList with function name
	else
		callList.push_back(new Call("", id, filename, type)); // add new call to callList without function name
	// always set mem to "" for new Call object
	mem = "";
}

// this is for getting rid of \n and commas
// again, I don't think this works, but needs to work for CSV file
void editArg(string &s, string search)
{
	std::size_t found;
	do{
		found = s.find(search);
  		if (found!=std::string::npos)
  			s.replace(found, 1, "");
  	}while(found!=std::string::npos);
}

//adds an argument to the last Call object in the list
bool Cparse::addArgument(int tabcount, bool tick, string a)
{
	if(checkcall(tabcount, tick)){
		// inside call block, but not in arg/mem block -> can add argument
		editArg(a, "\n"); // get rid of newlines
		editArg(a, ","); // get rid of commas
		int k = findCall(calltab.back()->identification);
		if(k != -1)
			callList[k]->addArg(a); // add argument to call in callList
		return true; // agument was added
	}
	return false; // argument was NOT added
}

//adds a BINOP or UNOP argument
//marks argument block
void Cparse::addOp(int tabcount, bool tick, string a)
{
	if(addArgument(tabcount, tick, a))
		markarg(tabcount);
}

//either saves member attribute name for later or adds member function name to latest Call object
void Cparse::addMem(int tabcount, bool tick, string attr)
{
	if(checkcall(tabcount, tick, true)){
		// in call block but not Arg/Mem block
		if((calltab.back()->type == 1) && !callList.back()->hasName()){
			// set name of member function and begin with OBJ (for library functions)
			addName("OBJ."+attr);
			markmemarg(tabcount); // in Mem block
		} else // attribute of member variable, not function -> add to mem variable
			mem = "."+attr+mem;
	} else if(!calltab.empty() && calltab.back()->memIsOn()){ // double member -> obj.func1().func2()
		calltab.back()->checkDM();
	}
}

//marks argument block and signals subscript type
void Cparse::addSub(int tabcount, bool tick)
{
	if(checkcall(tabcount, tick)){
		// in call block but not Arg/Mem block -> add argument
		sub = "[]"; // let program know to watch for a subscript argument
		markarg(tabcount); // in Arg block
	} else if(!calltab.empty() && calltab.back()->memIsOn()) {
		// in Mem block -> mark that it is also in Arg block, but do nothing else
		markarg(tabcount);
	}
}

//saves current function name
void Cparse::addFunction(int tabcount, bool tick, string f, bool memberfunc=false)
{
	checkblock(tabcount, tick); // always check if in a block
	if(memberfunc && !classtab.empty()){
		// add function Block with name of function as Class::function
		functab.push_back(new Block(tabcount, classtab.back()->name+"::"+f));
	} else{
		// function is not a member function -> just add Block with regular name
		functab.push_back(new Block(tabcount, f));
	}
}

// save the current class name
void Cparse::addClass(int tabcount, bool tick, string c)
{
	checkblock(tabcount, tick); // always check if in a block
	if(c != "definition"){ // this has to do with Clang AST
		//if only one Block in classtab and not in class definition, just overwrite Block object
		if(classtab.size() == 1 && !classtab.back()->on)
			classtab.back()->reinstate(tabcount, c);
		else // add a new Block object to classtab
			classtab.push_back(new Block(tabcount, c));
	}
}

//adds name of the function call to the last Call object in list
void Cparse::addName(string name)
{
	if(!calltab.empty()) // make sure there is actually a function call in calltab
		callList.back()->setName(name);

}

// add function call name to last Call object in list
void Cparse::addCallName(int tabcount, bool tick, string name)
{
	if(checkcall(tabcount, tick)){
		// in call block but not Arg/Mem block
		if(!calltab.empty()){
			if(!calltab.back()->type) // if the latest call is not a member function call
				addName(name);
		}
	}
}

//adds variable argument
//potential to be a member variable, so adds mem (if no mem, the value is "" and nothing happens)
void Cparse::addVar(int tabcount, bool tick, string a)
{
	if(addArgument(tabcount, tick, a+mem+sub)) // addArgument adds the argument, or sends back -1 if not added
		mem = "", sub = ""; // set both to "" to prepare for new argument
}

// adds Class name to function (dynamic dispatch)
void Cparse::addDynamicClass(int tabcount, bool tick, string c)
{
	checkcall(tabcount, tick); // always check if in block
	if(!calltab.empty() && calltab.back()->memIsOn() && !calltab.back()->argIsOn() && !calltab.back()->doublemem){
		// inside a call block, inside Mem block, not inside Arg block, and no double mem [ obj.func1().func2() ]
		callList.back()->appendName(c); // add Class to latest function call
	}
}

// saves filename
void Cparse::addFilename(string f)
{
	if(filename.find(".c") == -1) // if filename ends with .c or .cpp, leave be -> this is the program and everything after is defined in this program
  		filename = f;
}

//any Call without a name is tagged as **Undetermined_Function**
void Cparse::cleanUp()
{
	for(int k=0; k<callList.size(); k++){
		if(!callList[k]->hasName())
			callList[k]->setName("**Undetermined_Function**");
	}
}

//prints out the list of Calls
void Cparse::print()
{
	for(int k=0; k<callList.size(); k++){
		cout << callList[k]->print() << endl;
	}
}
