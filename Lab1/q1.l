%{
#include <stdio.h>
#include <stdlib.h>
int err = 1; /* for reporting error*/
%}

DG [0-9]
LR [a-zA-Z]
ID {LR}({LR}|{DG})*
INT_CONST {DG}+
FLT_CONST {DG}+\.{DG}+

%%
"int" {printf("Line %d: KEYWORD(int)\n", err);}
"float" {printf("Line %d: KEYWORD(float)\n", err);}
"if" {printf("Line %d: KEYWORD(if)\n", err);}
"else" {printf("Line %d: KEYWORD(else)\n", err);}
"while" {printf("Line %d: KEYWORD(while)\n", err);}
"print" {printf("Line %d: KEYWORD(print)\n", err);}

{FLT_CONST} {printf("Line %d: FLT_CONST(%s)\n", err, yytext);}
{INT_CONST} {printf("Line %d: INT_CONST(%d)\n", err, atoi(yytext));}

{ID} {printf("Line %d: IDENTIFIER(%s)\n",err,yytext);}

"+" {printf("Line %d: ARITH_OP(+, plus)\n",err);}
"-" {printf("Line %d: ARITH_OP(-, minus)\n",err);}
"*" {printf("Line %d: ARITH_OP(*, multiply)\n", err);}
"/" {printf("Line %d: ARITH_OP(/, divide)\n",err);}
"%" {printf("Line %d: ARITH_OP(%%, modulus)\n",err);}

"==" {printf("Line %d: REL_OP(==, equal to)\n",err);}
"!=" {printf("Line %d: REL_OP(!=, not equal to)\n",err);}
"<=" {printf("Line %d: REL_OP(<=, less than equal to)\n",err);}
">=" {printf("Line %d: REL_OP(>=, greater than equal to)\n",err);}
"<"  {printf("Line %d: REL_OP(<, less than)\n",err);}
">"  {printf("Line %d: REL_OP(>, greater than)\n",err);}

"&&" {printf("Line %d: BOOL_OP(&&, and)\n", err);}
"||" {printf("Line %d: BOOL_OP(||,or)\n",err);}
"!"  {printf("Line %d: BOOL_OP(!, not)\n",err);}

"=" {printf("Line %d: ASSIGN_OP(=)\n",err);}

";" {printf("Line %d: PUNCT(; semicolon)\n",err);}
"," {printf("Line %d: PUNCT(, comma)\n",err);}
"(" {printf("Line %d: Left Parenthesis\n",err);}
")" {printf("Line %d: Right Parenthesis\n",err);}
"{" {printf("Line %d: Left Curly\n",err);}
"}" {printf("Line %d: Right Curly\n",err);}

[\t \r]+ ;
\n {err++ ;}
. {printf("Line %d:LEXICAL ERROR - Unknown char:%s\n",err,yytext);}

%%

int yywrap() {
 return 1;
}

int main() {
 extern FILE *yyin;
 yyin = fopen("input.txt","r");
 
 if (!yyin) {
     printf("Error: Could not open file named 'input'\n");
     return 1;
 }

 printf("Starting Lexical Analysis\n");
 yylex();
 printf("Lexical Analysis Complete\n");
 return 0;
}