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
	#include "DoxConvert.tab.hpp"
%}

%%

	/* function call name */
"\""(\\.|[^"\\])*"\""								{
														yytext[strlen(yytext)-1] = 0;
														yylval.str = strdup(&yytext[1]);
														return STRING;
													}
	/* edge */
"Node"[0-9]+										{
														yylval.str = strdup(yytext);
														return NODE;
													}
	/* label is the name of the node */
"label"												{
														return LABEL;
													}
	/* vector */
"->"												{
														return ARROW;
													}

	/* whitespace */
[ \t\r\n]											{ }

	/* everything else */
.													{ }

%%

int yywrap(void) {
	return 1;
}