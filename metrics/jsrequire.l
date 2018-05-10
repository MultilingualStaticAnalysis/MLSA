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
	#include "jsrequire.tab.hpp"
%}

%%
	/* require */
[^.]"require("																			{
																						yylval.str = strdup(yytext);
																						return REQUIRE;
																					}
	/* parentheses and square brackets */
")"|"["|"]"|","																		{
																						return *yytext;
																					}

	/* string with double quotes for included file */
"\""(\\.|[^"\\])*"\""																{
																						yytext[strlen(yytext)-1] = 0;
																						yylval.str = strdup(&yytext[1]);
																						return DQSTRING; 
																					}

	/* string with single quotes for included file */
"'"(\\.|[^'\\])*"'"																	{
																						yytext[strlen(yytext)-1] = 0;
																						yylval.str = strdup(&yytext[1]);
																						return SQSTRING;
																					}

	/* single line comment */
"//"[^\n]*																			{ }

	/* multiple line comment */
"/*"([^*]|(\*+[^*/]))*\*+\/ 														{ }

[ \t\r\n]																			{ }

	/* everything else */
.																					{ }

%%

int yywrap(void) {
	return 1;
}
