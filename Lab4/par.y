%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int err;
extern char* yytext;
extern FILE *yyin;

int err_cnt = 0;
void yyerror(const char *msg);

typedef struct N {
    char *l;
    struct N *L, *M, *R;
} N;

N *rt = NULL;

N* mN(char *l, N *L, N *M, N *R) {
    N *n = (N*)malloc(sizeof(N));
    n->l = l ? strdup(l) : strdup("ERR");
    n->L = L; n->M = M; n->R = R;
    return n;
}

N* mL(char *l) { return mN(l, NULL, NULL, NULL); }

void pT(N *n, int lv) {
    if(!n || !n->l) return;
    if(lv > 0) {
        for(int i=0; i<lv-1; i++) printf("|   ");
        printf("|-- ");
    }
    printf("%s\n", n->l);
    pT(n->L, lv+1); pT(n->M, lv+1); pT(n->R, lv+1);
}

void pLMD(N *n) {
    if(!n || !n->l) return;
    if(n->L || n->M || n->R) {
        printf("  => %s -> ", n->l);
        if(n->L) printf("%s ", n->L->l);
        if(n->M) printf("%s ", n->M->l);
        if(n->R) printf("%s ", n->R->l);
        printf("\n");
    }
    pLMD(n->L); pLMD(n->M); pLMD(n->R);
}

void pRMD(N *n) {
    if(!n || !n->l) return;
    if(n->L || n->M || n->R) {
        printf("  => %s -> ", n->l);
        if(n->L) printf("%s ", n->L->l);
        if(n->M) printf("%s ", n->M->l);
        if(n->R) printf("%s ", n->R->l);
        printf("\n");
    }
    pRMD(n->R); pRMD(n->M); pRMD(n->L);
}
%}

%union { char *s; struct N *n; }

%error-verbose

%token INT FLOAT IF ELSE WHILE PRINT
%token <s> ID ICON FCON
%token PLUS MINUS MUL DIV MOD EQ NEQ LT GT LEQ GEQ AND OR NOT
%token ASGN SEMI COMMA LP RP LC RC

%type <n> P SL S B D T A Pr I W E

%right ASGN
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GEQ
%left PLUS MINUS
%left MUL DIV MOD
%right NOT

%start P

%%

P: SL { rt = $1; } ;

SL: S SL { $$ = mN("SL", $1, $2, NULL); }
  | error SEMI SL { yyerrok; $$ = $3; }
  | error RC SL { yyerrok; $$ = $3; }
  | { $$ = NULL; }
  ;

S: D {$$=$1;} | A {$$=$1;} | I {$$=$1;} | W {$$=$1;} | Pr {$$=$1;} | B {$$=$1;} ;

B: LC SL RC { $$ = mN("Blk", $2, NULL, NULL); } ;

D: T ID SEMI { $$ = mN("Decl", $1, mL($2), NULL); } 
 | T ID error { 
     fprintf(stderr, "\nLine %d: [!] SPECIFIC ERROR - Missing ';' after declaration of '%s'\n", err-1, $2);
     yyerrok; $$ = NULL; 
   }
 ;

T: INT { $$=mL("int"); } | FLOAT { $$=mL("float"); } ;

A: ID ASGN E SEMI { $$ = mN("Asgn", mL($1), $3, NULL); } 
 | ID ASGN E error { 
     fprintf(stderr, "\nLine %d: [!] SPECIFIC ERROR - Missing ';' after assignment to '%s'\n", err-1, $1);
     yyerrok; $$ = NULL; 
   }
 ;

Pr: PRINT LP ID RP SEMI { $$ = mN("Prnt", mL($3), NULL, NULL); } ;

I: IF LP E RP B { $$ = mN("If", $3, $5, NULL); }
 | IF LP E RP B ELSE B { $$ = mN("IfElse", $3, $5, $7); }
 ;

W: WHILE LP E RP B { $$ = mN("Whl", $3, $5, NULL); } 
 | WHILE error B { 
     fprintf(stderr, "\nLine %d: [!] SPECIFIC ERROR - Malformed 'while' condition\n", err);
     yyerrok; $$ = NULL; 
   }
 ;

E: E OR E  { $$ = mN("||", $1, $3, NULL); }
 | E AND E { $$ = mN("&&", $1, $3, NULL); }
 | E EQ E  { $$ = mN("==", $1, $3, NULL); }
 | E NEQ E { $$ = mN("!=", $1, $3, NULL); }
 | E LT E  { $$ = mN("<", $1, $3, NULL); }
 | E GT E  { $$ = mN(">", $1, $3, NULL); }
 | E LEQ E { $$ = mN("<=", $1, $3, NULL); }
 | E GEQ E { $$ = mN(">=", $1, $3, NULL); }
 | E PLUS E { $$ = mN("+", $1, $3, NULL); }
 | E MINUS E { $$ = mN("-", $1, $3, NULL); }
 | E MUL E { $$ = mN("*", $1, $3, NULL); }
 | E DIV E { $$ = mN("/", $1, $3, NULL); }
 | E MOD E { $$ = mN("%", $1, $3, NULL); }
 | NOT LP E RP { $$ = mN("!", $3, NULL, NULL); }
 | LP E RP { $$ = $2; }
 | ID      { $$ = mL($1); }
 | ICON    { $$ = mL($1); }
 | FCON    { $$ = mL($1); }
 ;

%%

void yyerror(const char *msg) {
    err_cnt++;
    fprintf(stderr, "\nLine %d: [!] %s near '%s'\n", err, msg, yytext);
}

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error: Cannot open 'input' file.\n");
        return 1;
    }
    
    yydebug = 1;
    fprintf(stderr, "=== SHIFT-REDUCE PARSING TRACE ===\n\n");
    yyparse();
    
    if (err_cnt == 0) {
        printf("\n\n=== SUCCESS: NO SYNTAX ERRORS ===\n");
        printf("\nTree:\n"); pT(rt, 0);
        printf("\nLMD:\n"); pLMD(rt);
        printf("\nRMD:\n"); pRMD(rt);
        printf("\n");
    } else {
        printf("\n\n=== PARSING FAILED ===\n");
        printf("Total syntax errors found: %d\n", err_cnt);
        printf("Check the trace above for specific error details.\n\n");
    }
    
    return 0;
}