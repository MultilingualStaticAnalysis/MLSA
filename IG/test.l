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
	#include "test.tab.hpp"
%}

%%

	/* function declaration */
"-FunctionDecl"																{ return FUNC; }

"-CXXMethodDecl"|"-CXXConstructorDecl"|"-CXXDestructorDecl"					{ return MEMFUNC; }

"'"																			{ return *yytext; }

"|"																			{ 
																				yylval.str = strdup(yytext);
																				//cout << "TAB: " << yylval.str << endl;
																				return TAB;
																			}

"`"																			{
																				yylval.str = strdup(yytext);
																				//cout << "TICK: " << yylval.str << endl;
																				return TICK;
																			}

"-CXXRecordDecl"															{ return CLASSNAME; }

	/* function call */
"-CallExpr"																	{ return CALL; }

"-CXXMemberCallExpr"														{ return MEMCALL; }

"-ImplicitCastExpr"															{ return CAST; }

"-DeclRefExpr"																{ return REF; }

	/* literal argument */
"-IntegerLiteral"															{ return INT; }

	/* member variable arg */
"-MemberExpr"																{ return MEMBER; }

	/* binop or unop arg */
"-BinaryOperator"															{ return BINOP; }

"-UnaryOperator"															{ return UNOP; }

	/* string arg */
"-StringLiteral"															{ return STR; }

"Var"																		{ return VAR; }

"ParmVar"																	{ return PARMVAR; }

	/* subscript arg */
"-ArraySubscriptExpr"														{ return SUB; }

"Function"																	{ return FUNCTION; }

"class"|"struct"|"union"													{ return CLASS; }

	/* variable ID number */
"0x"[a-z0-9]*																{
																				yylval.str = strdup(yytext);
																				//cout << "ID: " << yylval.str << endl;
																				return ID;
																			}

	/* variable or function name */
[~a-zA-Z_-][a-zA-Z0-9_]*														{
																				yylval.str = strdup(yytext);
																				//cout << "NAME: " << yylval.str << endl;
																				return NAME;
																			}

"-"?[0-9]+"."?[0-9]*														{
																				yylval.str = strdup(yytext);
																				//cout << "Number: " << yylval.str << endl;
																				return NUMBER;
																			}

	/* string */
"\""(\\.|[^"\\])*"\""														{
																				//yytext[strlen(yytext)-1] = 0;
																				//yylval.str = strdup(&yytext[1]);
																				//cout << "STRING: " << yylval.str << endl;
																				yylval.str = strdup(yytext);
																				return STRING;
																			}

"||"|"'|"|"|'"|"operator|"													{ }

	/* whitespace */
[ \t\r\n]																	{ }

	/* everything else */
.																			{ }

%%

int yywrap(void) {
	return 1;
}
