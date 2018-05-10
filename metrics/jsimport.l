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
	#include "jsimport.tab.hpp"
%}

%%
	/* from */
"from"																				{
																						yylval.str = strdup(yytext);
																						return FROM;
																					}

	/* import */
"import"																			{
																						yylval.str = strdup(yytext);
																						return IMPORT;
																					}

	/* string with double quotes (in case a keyword is found in a string) */
"\""(\\.|[^"\\])*"\""																{
																						yytext[strlen(yytext)-1] = 0;
																						yylval.str = strdup(&yytext[1]);
																						return DQSTRING;
																					}

	/* string with single quotes (in case a keyword is found in a string) */
"'"(\\.|[^'\\])*"'"																	{
																						yytext[strlen(yytext)-1] = 0;
																						yylval.str = strdup(&yytext[1]);
																						return SQSTRING;
																					}

	/* included file - in string form */
[a-zA-Z0-9_/.\\{}=#*,]*																{
																						yylval.str = strdup(yytext);
																						return LAKE;
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
