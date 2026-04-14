%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
int err = 1; 
extern FILE *err_file; // NEW: Grabbing the error file pointer from Yacc!
%}

DG [0-9]
LR [a-zA-Z]
ID {LR}({LR}|{DG})*
ICON {DG}+
FCON {DG}+\.{DG}+

%%
"int"   { yylval.s = strdup("int"); return INT; }
"float" { yylval.s = strdup("float"); return FLOAT; }
"if"    { return IF; }
"else"  { return ELSE; }
"while" { return WHILE; }
"print" { return PRINT; }

{FCON}  { yylval.s = strdup(yytext); return FCON; }
{ICON}  { yylval.s = strdup(yytext); return ICON; }
{ID}    { yylval.s = strdup(yytext); return ID; }

"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MUL; }
"/"     { return DIV; }
"%"     { return MOD; }
"=="    { return EQ; }
"!="    { return NEQ; }
"<="    { return LEQ; }
">="    { return GEQ; }
"<"     { return LT; }
">"     { return GT; }
"&&"    { return AND; }
"||"    { return OR; }
"!"     { return NOT; }
"="     { return ASGN; }
";"     { return SEMI; }
","     { return COMMA; }
"("     { return LP; }
")"     { return RP; }
"{"     { return LC; }
"}"     { return RC; }

[\t ]+  ;
\n      { err++; }
.       { fprintf(err_file, "Line %d: [!] LEX ERROR: Unknown character '%s'\n", err, yytext); }

%%
int yywrap() { return 1; }