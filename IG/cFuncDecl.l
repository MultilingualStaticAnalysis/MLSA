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

"-CXXMethodDecl"|"-CXXConstructorDecl"|"-CXXDestructorDecl"		{ return MEMFUNC; }

"void"|"void *"													{ return VOID; }

"'"|"("|")"|","													{
																	//cout << strdup(yytext) << endl;
																	return *yytext;
																}

	/* variable ID number */
"0x"[a-z0-9]*													{
																	yylval.str = strdup(yytext);
																	//cout << "ID: " << yylval.str << endl;
																	return ID;
																}

	/* variable or function name */
[~a-zA-Z_-][a-zA-Z0-9_<>]*"()"?									{
																	yylval.str = strdup(yytext);
																	//cout << "NAME: " << yylval.str << endl;
																	return NAME;
																}

"..."															{ return INFINITE; }

"-"?[0-9]+"."?[0-9]*											{
																	yylval.str = strdup(yytext);
																	//cout << "Number: " << yylval.str << endl;
																	return NUMBER;
																}

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

	/* whitespace */
[ \t\r\n]														{ }

"(&)"|"(*)"														{ }

	/* everything else */
.																{ }

%%

int yywrap(void) {
	return 1;
}