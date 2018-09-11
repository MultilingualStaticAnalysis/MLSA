/* 	MLSA Multilingual Software Analysis
	This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
 	Call.cpp holds all the information for the function calls in the AST, including ID, scope (the function they are found in), name, and all arguments
 	Author: Anne Marie Bogar
 	Date: February 14, 2018
 	this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
 	Input: N/A
 	Output: N/A
*/

#include <iostream>
#include <string>
#include <vector>
#include "DotParse.h"
using namespace std;

DotParse::~DotParse(){
	for(int k=0; k<nodeList.size(); k++)
		delete nodeList[k];
	for(int j=0; j<flowList.size(); j++)
		delete flowList[j];
}

void DotParse::addNode(string i, string n, string a=""){
	if(a != "")
		a = ","+a;
	nodeList.push_back(new Node(i, n, a));
}

void DotParse::addFlow(string n1, string n2){
	flowList.push_back(new Flow(n1, n2));
}

void DotParse::createDot(){
	string s = "", c = "", a = "";
	for(int k=0; k<flowList.size(); k++){
		for(int j=0; j<nodeList.size(); j++){
			if(nodeList[j]->id == flowList[k]->scope)
				s = nodeList[j]->name;
			if(nodeList[j]->id == flowList[k]->call){
				c = nodeList[j]->name;
				a = nodeList[j]->args;
			}
		}
		dot.push_back(flowList[k]->call+","+s+","+c+a);
	}
}

void DotParse::print(){
	for(int k=0; k<dot.size(); k++){
		cout << dot[k] << endl;
	}
}