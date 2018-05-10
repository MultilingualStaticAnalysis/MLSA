%{
	#include <iostream>
	#include <string>
	using namespace std;
	void yyerror(string);
	union YYSTYPE {
		int val;
		char *str;
	};
	typedef union YYSTYPE YYSTYPE;
	#include "cFuncDecl.tab.hpp"
%}

%%

	/* function declaration */
"-FunctionDecl"													{ return FUNC; }

	/* member function declaration */
"-CXXMethodDecl"|"-CXXConstructorDecl"|"-CXXDestructorDecl"		{ return MEMFUNC; }

	/* must return the actual text (') to be used in Bison rule */
"'"																{ return *yytext; }

	/* variable ID number */
"0x"[a-z0-9]*													{
																	yylval.str = strdup(yytext);
																	cout << "ID: " << yylval.str << endl;
																	return ID;
																}

	/* variable or function name */
[~a-zA-Z_-][a-zA-Z0-9_<>]*"()"?									{
																	yylval.str = strdup(yytext);
																	cout << "NAME: " << yylval.str << endl;
																	return NAME;
																}

	/* number */
"-"?[0-9]+"."?[0-9]*											{
																	yylval.str = strdup(yytext);
																	//cout << "Number: " << yylval.str << endl;
																	return NUMBER;
																}
	/* filename, e.g \home\mlsa\bin\cFunCall2.py */
"/"[a-zA-Z0-9_/-]+"."[a-zA-Z]+									{
																	yylval.str = strdup(yytext);
																	//cout << "file: " << yylval.str << endl;
																	return FILENAME;
																}

	/* string */
"\""(\\.|[^"\\])*"\""											{
																	//yytext[strlen(yytext)-1] = 0;
																	//yylval.str = strdup(&yytext[1]);
																	//cout << "STRING: " << yylval.str << endl;
																	yylval.str = strdup(yytext);
																	return STRING;
																}

	/* water - whitespace */
[ \t\r\n]														{ }

	/* water - this is from when I was also collecting number of parameters */
"(&)"|"(*)"														{ }

	/* water - everything else */
.																{ }

%%

int yywrap(void) {
	return 1;
}