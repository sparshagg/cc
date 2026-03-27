%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_types.h"
#include "y.tab.h"
int err = 1;
int last_if_line = 1;
int last_while_line = 1;
int last_print_line = 1;
int last_printf_line = 1;
int last_id_line = 1;
%}

Added more functions

DG [0-9]
LR [a-zA-Z]
ID {LR}({LR}|{DG})*
ICON {DG}+
FCON {DG}+\.{DG}+
SCON \"([^\"\\\n]|\\.)*\"

%%
"int" {return INT;}
"float" {return FLOAT;}
"if" {last_if_line = err; return IF;}
"else" {return ELSE;}
"while" {last_while_line = err; return WHILE;}
"print" {last_print_line = err; return PRINT;}
"printf" {last_printf_line = err; return PRINTF;}

"//".* ;
{SCON} { yylval.str = strdup(yytext); return SCON; }
\"([^\"\\\n]|\\.)* { printf("Line %d:LEXICAL ERROR - Unterminated string literal\n", err); }
{FCON} { yylval.str = strdup(yytext); return FCON; }
{ICON} { yylval.str = strdup(yytext); return ICON; }
{ID}   { last_id_line = err; yylval.str = strdup(yytext); return ID; }

"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}

"==" {return EQ;}
"!=" {return NEQ;}
"<=" {return LEQ;}
">=" {return GEQ;}
"<" {return LT;}
">" {return GT;}

"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}

"=" {return ASGN;}

";" {return SEMI;}
"," {return COMMA;}
"(" {return LP;}
")" {return RP;}
"{" {return LC;}
"}" {return RC;}

[\t ]+ ;
\n {err++;}
. {printf("Line %d:LEXICAL ERROR - Unknown char:%s\n",err,yytext);}

%%

int yywrap() {
 return 1;
}
