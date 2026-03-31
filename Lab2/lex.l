%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
int err = 1;

void printToken(const char *token, const char *lexeme) {
    printf("<%s, %s>\n", token, lexeme);
}
%}

DG [0-9]
LR [a-zA-Z]
ID {LR}({LR}|{DG})*
ICON {DG}+
FCON {DG}+\.{DG}+

%%
"int" { printToken("INT", yytext); return INT; }
"float" { printToken("FLOAT", yytext); return FLOAT; }
"if" { printToken("IF", yytext); return IF; }
"else" { printToken("ELSE", yytext); return ELSE; }
"while" { printToken("WHILE", yytext); return WHILE; }
"print" { printToken("PRINT", yytext); return PRINT; }

{FCON} { yylval.str = strdup(yytext); printToken("FCON", yytext); return FCON; }
{ICON} { yylval.str = strdup(yytext); printToken("ICON", yytext); return ICON; }
{ID}   { yylval.str = strdup(yytext); printToken("ID", yytext); return ID; }

"+" { printToken("PLUS", yytext); return PLUS; }
"-" { printToken("MINUS", yytext); return MINUS; }
"*" { printToken("MUL", yytext); return MUL; }
"/" { printToken("DIV", yytext); return DIV; }
"%" { printToken("MOD", yytext); return MOD; }

"==" { printToken("EQ", yytext); return EQ; }
"!=" { printToken("NEQ", yytext); return NEQ; }
"<=" { printToken("LEQ", yytext); return LEQ; }
">=" { printToken("GEQ", yytext); return GEQ; }
"<" { printToken("LT", yytext); return LT; }
">" { printToken("GT", yytext); return GT; }

"&&" { printToken("AND", yytext); return AND; }
"||" { printToken("OR", yytext); return OR; }
"!" { printToken("NOT", yytext); return NOT; }

"=" { printToken("ASGN", yytext); return ASGN; }

";" { printToken("SEMI", yytext); return SEMI; }
"," { printToken("COMMA", yytext); return COMMA; }
"(" { printToken("LP", yytext); return LP; }
")" { printToken("RP", yytext); return RP; }
"{" { printToken("LC", yytext); return LC; }
"}" { printToken("RC", yytext); return RC; }

[\t \r]+ ;
\n {err++;}
. {printf("Line %d:LEXICAL ERROR - Unknown char:%s\n",err,yytext);}

%%

int yywrap() {
 return 1;
}
