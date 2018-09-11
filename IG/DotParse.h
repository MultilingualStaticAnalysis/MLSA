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
#ifndef DOTPARSE_H
#define DOTPARSE_H

class DotParse
{
	private:
		struct Node{
			string id;
			string name;
			string args;
			Node(string i, string n, string a="") : id(i), name(n), args(a) {}
		};
		struct Flow{
			string scope;
			string call;
			Flow(string s, string c) : scope(s), call(c) {}
		};
		vector<Node*> nodeList;
		vector<Flow*> flowList;
		vector<string> dot;

	public:
		DotParse() {}
		~DotParse();
		void addNode(string i, string n, string a="");
		void addFlow(string n1, string n2);
		void createDot();
		void print();
};

#endif