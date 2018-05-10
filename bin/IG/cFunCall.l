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
"-FunctionDecl"																{ return FUNC; }

	/* member function declaration */
"-CXXMethodDecl"|"-CXXConstructorDecl"|"-CXXDestructorDecl"					{ return MEMFUNC; }

	/* must return the actual text (') to be used in Bison rule */
"'"																			{ return *yytext; }

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
"-CXXRecordDecl"|"-RecordDecl"												{ return CLASSNAME; }

	/* function call */
"-CallExpr"																	{ return CALL; }

	/* member function call */
"-CXXMemberCallExpr"														{ return MEMCALL; }

	/* Dynamic Class keywords */
"-ImplicitCastExpr"|"-CXXOperatorCallExpr"|"-CXXThisExpr"|"-CXXBindTemporaryExpr"	{ return DYNAM; }

	/* keyword that starts like for argument (for subscript and member variables) */
"-DeclRefExpr"																{ return REF; }

	/* literal argument */
"-IntegerLiteral"															{ return INT; }

	/* member variable argument */
"-MemberExpr"																{ return MEMBER; }

	/* binop argument */
"-BinaryOperator"															{ return BINOP; }

	/* unop argument */
"-UnaryOperator"															{ return UNOP; }

	/* string argument */
"-StringLiteral"															{ return STR; }

	/* comes in same line as REF - keyword for variable name */
"Var"																		{ return VAR; }

	/* comes in same line as REF - keyword for variable name */
"ParmVar"																	{ return PARMVAR; }

	/* comes in same line as REF - keyword for member function name */
"CXXMethod"																	{ return MEMNAME; }

	/* subscript argument */
"-ArraySubscriptExpr"														{ return SUB; }

	/* comes in same line as REF - keyword for regular function name */
"Function"																	{ return FUNCTION; }

	/* keywords before name of class */
"class"|"struct"|"union"													{ return CLASS; }

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

int yywrap(void) {
	return 1;
}
