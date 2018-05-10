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
	#include "cinclude.tab.hpp"
%}

%%

	/* included file - can be .h or not */
[a-zA-Z0-9_/.\\{}=]*											{
														yylval.str = strdup(yytext);
														return IFILE;
													}
	/* included file - in string form */
"\""[a-zA-Z0-9_/.\\{}=# ]*"\""										{
														yytext[strlen(yytext)-1] = 0;
														yylval.str = strdup(&yytext[1]);
														return STRING;
													}
	/* #include */
"#include"												{
														yylval.str = strdup(yytext);
														return INCLUDE;
													}
	/* < and > are used for included files; ex: #include <stdio.h> */
"<"|">"													{ 
														return *yytext;
													}
	/* single line comment */
"//"[^\n]*												{ }

	/* multiple line comment */
"/*"([^*]|(\*+[^*/]))*\*+\/ 										{ }

	/* everything else */
.													{ }

%%

int yywrap(void) {
	return 1;
}
