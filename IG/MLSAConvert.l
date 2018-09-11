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
	#include "MLSAConvert.tab.hpp"
%}

%%

	/* edge */
"Node0x"[0-9]+										{
														yylval.str = strdup(yytext);
														return NODE;
													}

	/* function call name */
[a-zA-Z_][a-zA-Z0-9_~:.]*							{
														yylval.str = strdup(yytext);
														//cout << "WORD: " << yylval.str << endl;
														return WORD;
													}
	/* capture everything in parentheses */
"("([^)]+)")"										{
														yytext[strlen(yytext)-1] = 0;
														yylval.str = strdup(&yytext[1]);
														//cout << "ARGS: " << yylval.str << endl;
														return ARGS;
													}

"()"												{ return NOARGS; }

"/"[a-zA-Z0-9_/-]+"."[a-zA-Z]+						{
														yylval.str = strdup(yytext);
														return FILENAME;
													}

	/* label is the name of the node */
"\\n"												{
														//cout << "NEWLINE!!\n";
														return NEWLINE;
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