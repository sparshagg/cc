%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int err;
extern char* yytext;
extern FILE *yyin;

void yyerror(const char *s);

typedef struct ASTNode {
    char *label;
    struct ASTNode *left, *mid, *right;
} ASTNode;

ASTNode* makeNode(char *label, ASTNode *left, ASTNode *mid, ASTNode *right) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (label != NULL) {
        node->label = strdup(label);
    } else {
        node->label = strdup("MISSING_LABEL"); 
    }
    node->left = left;
    node->mid = mid;
    node->right = right;
    return node;
}

ASTNode* makeLeaf(char *label) {
    return makeNode(label, NULL, NULL, NULL);
}

void printTree(ASTNode *node, int level) {
    if (!node || !node->label) return;
    for(int i=0; i<level; i++) printf("  |__ ");
    printf("%s\n", node->label);
    printTree(node->left, level+1);
    printTree(node->mid, level+1);
    printTree(node->right, level+1);
}

void printLMD(ASTNode *node) {
    if(!node || !node->label) return;
    
    if (!node->left && !node->mid && !node->right) {
        printf("%s ", node->label);
        return;
    }
    
    printf("[ %s -> ", node->label);
    printLMD(node->left);
    printLMD(node->mid);
    printLMD(node->right);
    printf("] ");
}

void printRMD(ASTNode *node) {
    if(!node || !node->label) return;
    
    if (!node->left && !node->mid && !node->right) {
        printf("%s ", node->label);
        return;
    }
    
    printf("[ %s -> ", node->label);
    printRMD(node->right);
    printRMD(node->mid);
    printRMD(node->left);
    printf("] ");
}
%}

%union {
    char *str;
    struct ASTNode *node;
}

%token INT FLOAT IF ELSE WHILE PRINT
%token <str> ID ICON FCON
%token PLUS MINUS MUL DIV MOD EQ NEQ LT GT LEQ GEQ AND OR NOT
%token ASGN SEMI COMMA LP RP LC RC

%type <node> Prog StmtList Stmt Blk Decl Typ Asgn PrntStmt IfStmt WhlStmt Expr

/* Precedence and associativity */
%right ASGN
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GEQ
%left PLUS MINUS
%left MUL DIV MOD
%right NOT

%start Prog

%%

Prog: 
    StmtList { 
        printf("\n--- PARSE TREE ---\n");
        printTree($1, 0);
        printf("\n--- LEFTMOST DERIVATION (LMD) ---\n");
        printLMD($1);
        printf("\n\n--- RIGHTMOST DERIVATION (RMD) ---\n");
        printRMD($1);
        printf("\n\n");
    } 
    ;

StmtList: Stmt StmtList { $$ = makeNode("StmtList", $1, $2, NULL); } 
        | { $$ = NULL; } 
        ;

Stmt: Decl { $$ = $1; } | Asgn { $$ = $1; } | IfStmt { $$ = $1; } 
    | WhlStmt { $$ = $1; } | PrntStmt { $$ = $1; } | Blk { $$ = $1; } 
    ;

Blk: LC StmtList RC { $$ = makeNode("Block", $2, NULL, NULL); } 
   ;

Decl: Typ ID SEMI { $$ = makeNode("Decl", $1, makeLeaf($2), NULL); } 
    ;

Typ: INT { $$ = makeLeaf("int"); } | FLOAT { $$ = makeLeaf("float"); } 
   ;

Asgn: ID ASGN Expr SEMI { $$ = makeNode("Asgn(=)", makeLeaf($1), $3, NULL); } 
    ;

PrntStmt: PRINT LP ID RP SEMI { $$ = makeNode("Print", makeLeaf($3), NULL, NULL); } 
        ;

IfStmt: IF LP Expr RP Blk { $$ = makeNode("If", $3, $5, NULL); }
      | IF LP Expr RP Blk ELSE Blk { $$ = makeNode("If-Else", $3, $5, $7); }
      ;

WhlStmt: WHILE LP Expr RP Blk { $$ = makeNode("While", $3, $5, NULL); }
       ;

Expr: Expr OR Expr    { $$ = makeNode("||", $1, $3, NULL); }
    | Expr AND Expr   { $$ = makeNode("&&", $1, $3, NULL); }
    | Expr EQ Expr    { $$ = makeNode("==", $1, $3, NULL); }
    | Expr NEQ Expr   { $$ = makeNode("!=", $1, $3, NULL); }
    | Expr LT Expr    { $$ = makeNode("<", $1, $3, NULL); }
    | Expr GT Expr    { $$ = makeNode(">", $1, $3, NULL); }
    | Expr LEQ Expr   { $$ = makeNode("<=", $1, $3, NULL); }
    | Expr GEQ Expr   { $$ = makeNode(">=", $1, $3, NULL); }
    | Expr PLUS Expr  { $$ = makeNode("+", $1, $3, NULL); }
    | Expr MINUS Expr { $$ = makeNode("-", $1, $3, NULL); }
    | Expr MUL Expr   { $$ = makeNode("*", $1, $3, NULL); }
    | Expr DIV Expr   { $$ = makeNode("/", $1, $3, NULL); }
    | Expr MOD Expr   { $$ = makeNode("%", $1, $3, NULL); }
    | NOT LP Expr RP  { $$ = makeNode("!", $3, NULL, NULL); }
    | LP Expr RP      { $$ = $2; }
    | ID              { $$ = makeLeaf($1); }
    | ICON            { $$ = makeLeaf($1); }
    | FCON            { $$ = makeLeaf($1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "\n[!] SYNTAX ERROR: at line %d near '%s'\n", err, yytext);
}

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error: Could not open file named 'input'\n");
        return 1;
    }
    yyparse();
    return 0;
}
