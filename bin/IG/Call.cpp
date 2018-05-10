/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Call.cpp holds all the information for the function calls in the AST, including ID, scope (the function they are found in), name, and all arguments
 	Author: Anne Marie Bogar
 	Date: May 9, 2018
 	this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
 	Input: N/A
 	Output: N/A
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "Call.h"
using namespace std;

//constructor -> sets scope, id and filename, declares name as "", sets type to either MEMBER of GLOBAL
Call::Call(string s, string i, string f, int t)
{
	scope = s;
	id = i;
	filename = f;
	name = "";
	type = "GLOBAL";
	if(t)
		type = "MEMBER";
}

//sets the name of the Call
void Call::setName(string n)
{
	name = n;
}

//adds an argument to the Call's argument vector
void Call::addArg(string a)
{
	// remove all commas (,)
	// I honestly have no idea if this works
	// still need to remove all newlines (\n)
	a.erase(std::remove(a.begin(), a.end(), ','), a.end());
	args.push_back(a);
}

//returns true if name is not ""
bool Call::hasName()
{
	if(name != "")
		return true;
	return false;
}

// returns true if the ID given matches the call's id (for matching)
bool Call::sameID(string i)
{
	if(id == i)
		return true;
	return false;
}

// add Class name to name, e.g. Class::function
void Call::appendName(string n){
	if(name.find(':') == -1){ // no class yet
		if(name.find("OBJ.") != -1) //OBJ in name -> remove and add Class
			name.replace(0,4,n+"::");
		else // OBJ NOT in name -> just add class
			name = n+"::"+name;
	}
}

//returns a string of the Call in CSV form
//filename,ID,scope,name[,arg1][,arg2][...]
string Call::print()
{
	string p = filename+","+id+","+type+","+scope+","+name;
	for(int k=0; k<args.size(); k++){
		p += ","+args[k];
	}
	return p;
}
