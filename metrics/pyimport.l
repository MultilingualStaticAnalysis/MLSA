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
	#include "pyimport.tab.hpp"
%}

%%

	/* multiple line comment with single quotes */
"'''"(('[^'])|(''[^'])|[^'''])*"'''" 								{ }

	/* multiple line comment with double quotes */
"\"\"\""((\"[^"])|(\"\"[^"])|[^"""])*"\"\"\"" 							{ }

	/* string with double quotes (in case a keyword is found in a string) */
"\""(\\.|[^"\\])*"\""										{ }

	/* string with single quotes (in case a keyword is found in a string) */
"'"(\\.|[^'\\])*"'"

	/* IMPORT keyword; ex: import module */
"import"											{
													yylval.str = strdup(yytext);
													return IMPORT;
												}
	/* FROM keyword; ex: from module import function */
"from"												{
													yylval.str = strdup(yytext);
													return FROM;
												}

	/* included file */
[a-zA-Z0-9_/.\{}=]*										{
													yylval.str = strdup(yytext);
													return IFILE;
												}
	/* , used for multiple imports on one line; ex: import os, sys */
","												{
													return *yytext;
												}
	/* single line comment */
"#"[^\n]*											{ }

	/* everything else */
.												{ }

%%

int yywrap(void) {
	return 1;
}
