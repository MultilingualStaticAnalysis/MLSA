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
	#include "cFunCall.tab.hpp"
%}

%%

	/* function declaration */
"-FunctionDecl"																{
//cout << "TAB: " << yytext << endl;
 return FUNC; }

	/* member function declaration */
"-CXXMethodDecl"|"-CXXConstructorDecl"|"-CXXDestructorDecl"					{//cout << "TAB: " << yytext << endl;
 return MEMFUNC; }

	/* must return the actual text (') to be used in Bison rule */
"'"																			{//cout << "TAB: " << yytext << endl;
 return *yytext; }

	/* tab in AST (sets apart blocks) */
"|"																			{
																				yylval.str = strdup(yytext);
																				//cout << "TAB: " << yylval.str << endl;
																				return TAB;
																			}

	/* tick in AST (shows that the line is still inside the block) */
"`"																			{
																				yylval.str = strdup(yytext);
																				//cout << "TICK: " << yylval.str << endl;
																				return TICK;
																			}

	/* class declaraction */
"-CXXRecordDecl"|"-RecordDecl"									    {// cout << "TAB: " <<  yytext << endl;
 return CLASSNAME; }

	/* function call */
"-CallExpr"																	{//cout << "TAB: " << yytext << endl; 
return CALL; }

	/* member function call */
"-CXXMemberCallExpr"											{//cout << "TAB: " << yytext << endl; return MEMCALL; }

	/* Dynamic Class keywords */
"-ImplicitCastExpr"|"-CXXOperatorCallExpr"|"-CXXThisExpr"|"-CXXBindTemporaryExpr"	{//cout << "TAB: " << yytext << endl; 
return DYNAM; }

	/* keyword that starts like for argument (for subscript and member variables) */
"-DeclRefExpr"																{     //cout << "TAB: " << yytext << endl;
 return REF; }

	/* literal argument */
"-IntegerLiteral"															{     //cout << "TAB: " << yytext << endl; 
return INT; }

	/* member variable argument */
"-MemberExpr"																{     //cout << "TAB: " << yytext << endl; 
return MEMBER; }

	/* binop argument */
"-BinaryOperator"															{     //cout << "TAB: " << yytext << endl;
 return BINOP; }

	/* unop argument */
"-UnaryOperator"															{     //cout << "TAB: " << yytext << endl;
 return UNOP; }

	/* string argument */
"-StringLiteral"															{     //cout << "TAB: " << yytext << endl; 
return STR; }

	/* comes in same line as REF - keyword for variable name */
"Var"																		{//cout << "TAB: " << yytext << endl;
 return VAR; }

	/* comes in same line as REF - keyword for variable name */
"ParmVar"																	{//cout << "TAB: " << yytext << endl;
 return PARMVAR; }

	/* comes in same line as REF - keyword for member function name */
"CXXMethod"																	{//cout << "TAB: " << yytext << endl; 
return MEMNAME; }

	/* subscript argument */
"-ArraySubscriptExpr"														{             //cout << "TAB: " << yytext << endl;
 return SUB; }

	/* comes in same line as REF - keyword for regular function name */
"Function"																	{//cout << "TAB: " << yytext << endl;
 return FUNCTION; }

	/* keywords before name of class */
"class"|"struct"|"union"													{             //cout << "TAB: " << yytext << endl;
 return CLASS; }

	/* variable ID number */
"0x"[a-z0-9]*																{
																				yylval.str = strdup(yytext);
																				// **line below for debugging IG
																				//cout << "ID: " << yylval.str << endl;
																	
return ID;
																			}

	/* variable or function name */
[~a-zA-Z_-][a-zA-Z0-9_:-]*														{
																				yylval.str = strdup(yytext);
																				// **line below for debugging IG
																				//cout << "NAME: " << yylval.str << endl;
																	
return NAME;
																			}

	/* number */
"-"?[0-9]+"."?[0-9]*														{
																				yylval.str = strdup(yytext);
																				// **line below for debugging IG
																				//cout << "Number: " << yylval.str << endl;
																				
 return NUMBER;
																			}

	/* string */
"\""(\\.|[^"\\])*"\""														{
																				yytext[strlen(yytext)-1] = 0;
																				yylval.str = strdup(&yytext[1]);
																				// **line below for debugging IG
																				//cout << "STRING: " << yylval.str << endl;
																				
 return STRING;
																			}

	/* filename ex: \home\mlsa\bin\cFunCall2.py */
"/"[a-zA-Z0-9_/-]+"\.\."*[a-zA-Z0-9_/-]+"."[a-zA-Z]+						{
																				yylval.str = strdup(yytext);
																				
return FILENAME;
																			}

	/* water - anything that looks like a tab in AST but is not a tab */
"||"|"'|"|"|'"|"operator|"|"operator||"										{ }

	/* water - whitespace */
[ \t\r\n]																	{ }

	/* water - everything else */
.																			{ }

%%

int yywrap(void) 
{
	return 1;
}





