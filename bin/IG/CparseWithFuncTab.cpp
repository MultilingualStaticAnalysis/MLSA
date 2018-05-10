/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Cparse.cpp processes strings found in the C/C++ Island Grammar to print out a CSV with all function calls that include their ID, scope (the function they are found in), name, and all arguments
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
#include <typeinfo>
#include <vector>
#include "CparseWithFuncTab.h"
#include "Call.h"
using namespace std;

//default constructor -> set starting values for member variables
Cparse::Cparse()
{
	arg = false;
	memarg = false;
	sub = "";
	mem = "";
	classname = "";
	filename = "";
}

//destructor -> delete all Call pointers and Callblock pointers
Cparse::~Cparse()
{
	for(int k=0; k<callList.size(); k++){
		delete callList[k];
	}
	for(int j=0; j<calltab.size(); j++){
		delete calltab[j];
	}
}

//checks whether the AST is in an argument block or a member argument block
//if in block, do not add argument unless it is the name of a subscript variable
bool Cparse::checkarg(int tabcount, bool tick, bool memcall)
{
	if(arg){
		//checks whether the argument block has finished
		if((argtab > tabcount)||((argtab == tabcount)&&(!tick))){
			arg = false;
			mem = "";
			return true;
		} else if(sub == "[]"){
			return true;
		} else if(memcall && !memarg){
			return true;
		} else {
			return false;
		}
	}
	if(memarg){
		//checks whether the member argument block has finished
		if((memtab > tabcount)||((memtab == tabcount)&&(!tick))){
			mem = "";
			memarg = false;
			return true;
		} else {
			return false;
		}
	}
	return true;
}

//the AST is in an argument block
void Cparse::markarg(int tabcount)
{
	arg = true;
	argtab = tabcount;
}

//the AST is in a member argument block
void Cparse::markmemarg(int tabcount)
{
	memarg = true;
	memtab = tabcount;
}

//checks whether a call block has finished
//if the indent is smaller than or equal to the call indent and there is no tick, the call block has finished
void Cparse::checkblock(int tabcount, bool tick)
{
	int tabs = calltab.size();
	for(int k = 0; k < tabs; k++){
		if((calltab.back()->indent > tabcount)||((calltab.back()->indent == tabcount)&&(!tick))){
			delete calltab.back();
			calltab.pop_back();
		}
	}
}

void Cparse::checkfunction(int tabcount, bool tick)
{
	int tabs = functiontab.size();
	for(int k = 0; k < tabs; k++){
		if((functiontab.back()->indent > tabcount)||((functiontab.back()->indent == tabcount)&&(!tick))){
			delete functiontab.back();
			functiontab.pop_back();
		}
	}
}

//checks whether the AST is inside a call block or an argument block
bool Cparse::checkcall(int tabcount, bool tick, bool memcall=false)
{
	checkfunction(tabcount, tick);
	checkblock(tabcount, tick);
	if(calltab.empty()){
		memarg = false;
		mem = "";
		arg = false;
		return false;
	} else {
		return checkarg(tabcount, tick, memcall);
	}
}

int Cparse::findCall(string i)
{
	for(int k=0; k<callList.size(); k++){
		if(callList[k]->sameID(i))
			return k;
	}
	return -1;
}

//adds a new Call object to the list and a new Callblock object depending on the type of call
void Cparse::addCall(int type, int tabcount, bool tick, string id)
{
	cout << "inside addCall\n";
	checkcall(tabcount, tick);
	cout << "after checkcall\n";
	if(type && memarg){
		memarg = false;
		mem = "";
		delete calltab.back();
		calltab.pop_back();
	} else {
		if(!calltab.empty() && !arg){
			int k = findCall(calltab.back()->identification);
			if(k != -1)
				callList[k]->addArg(id);
		}
	}
	calltab.push_back(new Callblock(type, tabcount, id));
	cout << "adding new to callList\n";
	callList.push_back(new Call(functiontab.back()->name, id, filename, type));
	mem = "";
}

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
		editArg(a, "\n");
		editArg(a, ",");
		int k = findCall(calltab.back()->identification);
		if(k != -1)
			callList[k]->addArg(a);
		return true;
	}
	return false;
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
		if((calltab.back()->type == 1) && !callList.back()->hasName()){
			addName("OBJ."+attr);
			markmemarg(tabcount);
		} else
			mem = "."+attr+mem;
	}
}

//marks argument block and signals subscript type
void Cparse::addSub(int tabcount, bool tick)
{
	if(checkcall(tabcount, tick)){
		sub = "[]"; 
		markarg(tabcount);
	} else if(memarg) {
		markarg(memarg);
	}
}

//saves current function name
void Cparse::addFunction(int tabcount, bool tick, string f, bool memberfunc=false)
{
	checkfunction(tabcount, tick);
	checkblock(tabcount, tick);
	if(memberfunc)
		functiontab.push_back(new Functionblock(tabcount, classname+"::"+f));
	else
		functiontab.push_back(new Functionblock(tabcount, f));
	cout << "Number of functions: "+to_string(functiontab.size()) << endl;
}

void Cparse::addClass(int tabcount, bool tick, string c)
{
	checkfunction(tabcount, tick);
	checkblock(tabcount, tick);
	if(c != "definition")
		classname = c;
}

//adds name of the function call to the last Call object in list
void Cparse::addName(string name)
{
	if(!calltab.empty())
		callList.back()->setName(name);

}

void Cparse::addCallName(string name)
{
	if(!calltab.empty()){
		if(!calltab.back()->type)
			addName(name);
	}
}

//adds variable argument
//potential to be a member variable, so adds mem (if no mem, the value is "" and nothing happens)
void Cparse::addVar(int tabcount, bool tick, string a)
{
	//cout << "Adding Var: " << mem << endl;
	if(addArgument(tabcount, tick, a+mem+sub))
		mem = "", sub = "";
}

//adds Parameter variable argument
//potential to be subscript variable, so adds sub (if no sub, value is "" and nothing happens)
void Cparse::addParmVar(int tabcount, bool tick, string a)
{
	if(addArgument(tabcount, tick, a+mem+sub))
		sub = "", mem = "";
}

void Cparse::addDynamicClass(int tabcount, bool tick, string c)
{
	//cout << c << endl;
	if(!checkcall(tabcount, tick) || || (calltab.back()->type)){
		if((memarg || calltab.back()->type) && !arg)// && c != "std" && c.find("std::") == std::string::npos)
			callList.back()->appendName(c);
	}
}

void Cparse::addFilename(string f)
{
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
