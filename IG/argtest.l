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
	#include "argtest.tab.hpp"
%}

%%

	/* function declaration */
"-FunctionDecl"						{ 	yylval.str = strdup(yytext);
										return FUNC; 
									}

"'"									{ return *yytext; }

	/* function call */
"-CallExpr"							{ return CALL; }

	/* literal argument */
"-IntegerLiteral"					{ return INT; }

	/* member variable arg */
"-MemberExpr"						{ return MEMBER; }

	/* binop or unop arg */
"-BinaryOperator"					{ return BINOP; }

"-UnaryOperator"					{ return UNOP; }

	/* string arg */
"-StringLiteral"					{ return STR; }

"Var"								{ return VAR; }

	/* subscript arg */
"-ArraySubscriptExpr"				{ return SUB; }

"ParmVar"							{ return PVAR; }

[a-zA-Z]*"Stmt"						{ return NODE; }

	/* variable ID number */
"0x"[a-z0-9]*						{
										yylval.str = strdup(yytext);
										cout << "ID: " << yylval.str << endl;
										return ID;
									}

	/* variable or function name */
[a-zA-Z|_][a-zA-Z0-9|_]*				{
										yylval.str = strdup(yytext);
										cout << "NAME: " << yylval.str << endl;
										return NAME;
									}

"-"?[0-9]+"."?[0-9]*				{
										yylval.str = strdup(yytext);
										cout << "Number: " << yylval.str << endl;
										return NUMBER;
									}

	/* string */
"\""(\\.|[^"\\])*"\""				{
										yytext[strlen(yytext)-1] = 0;
										yylval.str = strdup(&yytext[1]);
										cout << "STRING: " << yylval.str << endl;
										return STRING;
									}

	/* whitespace */
[ \t\r\n]							{ }

	/* everything else */
.									{ }

%%

int yywrap(void) {
	return 1;
}
