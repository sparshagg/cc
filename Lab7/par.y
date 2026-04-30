%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h" 
#include "tac.h" 

extern int yylex();
extern int err;
extern char* yytext;
extern FILE *yyin;
int err_cnt = 0;
int sem_err_cnt = 0; 
int curr_scope = 0;  
FILE *err_file; 

void yyerror(const char *msg);
typedef struct N {
    char *l;
    char *type; 
    struct N *L, *M, *R;
} N;
N *rt = NULL;

N* mN(char *l, N *L, N *M, N *R, char *type) {
    N *n = (N*)malloc(sizeof(N));
    n->l = l ? strdup(l) : strdup("ERR");
    n->type = type ? strdup(type) : strdup("void");
    n->L = L; n->M = M;
    n->R = R;
    return n;
}

N* mL(char *l, char *type) { return mN(l, NULL, NULL, NULL, type);
}

void pT(N *n, int lv) {
    if(!n || !n->l) return;
    if(lv > 0) {
        for(int i=0; i<lv-1; i++) printf("|   ");
        printf("|-- ");
    }
    printf("%s (Type: %s)\n", n->l, n->type);
    pT(n->L, lv+1); pT(n->M, lv+1); pT(n->R, lv+1);
}
%}

%union { char *s; struct N *n; }

%error-verbose
%debug

%token <s> INT FLOAT
%token IF ELSE WHILE PRINT
%token <s> ID ICON FCON
%token PLUS MINUS MUL DIV MOD EQ NEQ LT GT LEQ GEQ AND OR NOT
%token ASGN SEMI COMMA LP RP LC RC

%type <n> P SL S B D T A Pr I W E 
%type <s> PrntID  

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

P: { init_symtab();
} SL { rt = $2; } ;

SL: S SL { $$ = mN("SL", $1, $2, NULL, "void");
}
  | error SEMI SL { yyerrok; $$ = $3; }
  | { $$ = NULL;
}
  ;

S: D {$$=$1;} | A {$$=$1;} | I {$$=$1;} | W {$$=$1;} | Pr {$$=$1;} |
B {$$=$1;} ;

B: LC { curr_scope++; } SL RC { 
     delete_scope(curr_scope); 
     curr_scope--;
     $$ = mN("Blk", $3, NULL, NULL, "void"); 
   } ;

D: T ID SEMI { 
     if (!insert_sym($2, $1->l, curr_scope, err)) {
         fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Redeclaration of '%s'.\n", err, $2);
         sem_err_cnt++;
     }
     $$ = mN("Decl", $1, mL($2, $1->l), NULL, "void"); 
   } 
 ;
T: INT { $$=mL("int", "type"); } | FLOAT { $$=mL("float", "type"); } ;
A: ID ASGN E SEMI { 
     sym_record *sym = lookup_sym($1, curr_scope);
     if (sym == NULL) {
         fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Undeclared variable '%s'.\n", err, $1);
         sem_err_cnt++;
     } else {
         sym->is_initialized = 1;
         if (strcmp(sym->type, $3->type) != 0 && strcmp($3->type, "error") != 0) {
             if (strcmp(sym->type, "float") == 0 && strcmp($3->type, "int") == 0) {
                 // Implicit cast allowed
             } else {
                 fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Type mismatch. Cannot assign '%s' to '%s' (type '%s').\n", 
err, $3->type, $1, sym->type);
                 sem_err_cnt++;
             }
         }
     }
     $$ = mN("Asgn", mL($1, sym?sym->type:"error"), $3, NULL, "void");
} 
 ;

PrntID: ID {
    sym_record *sym = lookup_sym($1, curr_scope);
    if (sym == NULL) {
        fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Undeclared variable '%s' in print.\n", err, $1);
        sem_err_cnt++;
    } else if (!sym->is_initialized) {
        fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Uninitialized variable '%s' used in print.\n", err, $1);
        sem_err_cnt++;
    }
    $$ = $1;
};

Pr: PRINT LP PrntID RP SEMI { $$ = mN("Prnt", mL($3, "id"), NULL, NULL, "void");
} ;

I: IF LP E RP B { $$ = mN("If", $3, $5, NULL, "void"); }
 |
IF LP E RP B ELSE B { $$ = mN("IfElse", $3, $5, $7, "void"); }
 ;
W: WHILE LP E RP B { $$ = mN("Whl", $3, $5, NULL, "void"); } ;
E: E OR E  { $$ = mN("||", $1, $3, NULL, "bool"); }
 |
E AND E { $$ = mN("&&", $1, $3, NULL, "bool"); }
 |
E EQ E  { $$ = mN("==", $1, $3, NULL, "bool"); }
 |
E NEQ E { $$ = mN("!=", $1, $3, NULL, "bool"); }
 |
E LT E  { $$ = mN("<", $1, $3, NULL, "bool"); }
 |
E GT E  { $$ = mN(">", $1, $3, NULL, "bool"); }
 |
E LEQ E { $$ = mN("<=", $1, $3, NULL, "bool"); }
 |
E GEQ E { $$ = mN(">=", $1, $3, NULL, "bool"); }
 
 |
E PLUS E { 
      char *t = "int";
      if (strcmp($1->type, "float") == 0 || strcmp($3->type, "float") == 0) t = "float";
      $$ = mN("+", $1, $3, NULL, t);
}
 | E MINUS E { 
      char *t = "int";
      if (strcmp($1->type, "float") == 0 || strcmp($3->type, "float") == 0) t = "float";
      $$ = mN("-", $1, $3, NULL, t);
}
 | E MUL E { 
      char *t = "int";
      if (strcmp($1->type, "float") == 0 || strcmp($3->type, "float") == 0) t = "float";
      $$ = mN("*", $1, $3, NULL, t);
}
 | E DIV E { 
      char *t = "int";
      if (strcmp($1->type, "float") == 0 || strcmp($3->type, "float") == 0) t = "float";
      $$ = mN("/", $1, $3, NULL, t);
}
   
 | E MOD E { 
      if (strcmp($1->type, "float") == 0 || strcmp($3->type, "float") == 0) {
          fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Modulo '%%' cannot be applied to floats.\n", err);
          sem_err_cnt++;
      }
      $$ = mN("%", $1, $3, NULL, "int"); 
   }
 |
NOT LP E RP { $$ = mN("!", $3, NULL, NULL, "bool"); }
 |
LP E RP { $$ = $2; }
 
 |
ID { 
      sym_record *sym = lookup_sym($1, curr_scope);
      char *t = "error";
      if (sym == NULL) {
         fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Undeclared variable '%s'.\n", err, $1);
         sem_err_cnt++;
      } else {
         t = sym->type;
         if (!sym->is_initialized) {
             fprintf(err_file, "Line %d: [!] SEMANTIC ERROR: Uninitialized variable '%s' used in math.\n", err, $1);
             sem_err_cnt++;
         }
      }
      $$ = mL($1, t); 
   }
 |
ICON    { $$ = mL($1, "int"); }
 | FCON    { $$ = mL($1, "float");
}
 ;

%%

void yyerror(const char *msg) {
    err_cnt++;
    fprintf(err_file, "Line %d: [!] SYNTAX ERROR: %s near '%s'\n", err, msg, yytext);
}

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("[!] ERROR: Could not find 'input.txt' file.\n");
        return 1;
    }
    
    // Direct error messages to standard output
    err_file = stdout; 
    
    // ENABLE verbose shift/reduce trace for LALR(1) demonstration
    yydebug = 1; 
    printf("\n--- 1. LALR(1) SHIFT-REDUCE PARSER TRACE ---\n");
    
    init_tac(); 
    
    // yyparse() will now print state transitions and shifts/reductions to the console
    yyparse();
    
    if (err_cnt == 0 && sem_err_cnt == 0) {
        printf("\n==========================================================\n");
        printf("=== SUCCESS: NO SYNTAX OR SEMANTIC ERRORS DETECTED ===\n");
        printf("==========================================================\n");
        
        printf("\n--- 2. ABSTRACT SYNTAX TREE ---\n"); 
        pT(rt, 0);
        
        printf("\n--- 3. SYMBOL TABLE ---\n");
        print_symtab(); 
        
        // Phase 4: TAC Generation
        generate_tac(rt);
        print_quadruples();
        
        // Phase 5: Optimization (Constant Folding)
        optimize_tac(); 
        print_optimized_quadruples();

        // Phase 6: Target Assembly Code Generation
        generate_assembly();
        
        printf("\n[+] 0 Errors detected! Compilation successful.\n");
    } else {
        printf("\n==========================================================\n");
        printf("=== COMPILATION FAILED ===\n");
        printf("- Syntax Errors: %d\n", err_cnt);
        printf("- Semantic Errors: %d\n", sem_err_cnt);
        printf("==========================================================\n");
    }
    
    return 0;
}
