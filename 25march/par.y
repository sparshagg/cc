%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_types.h"

extern int yylex();
extern int err;
extern int last_if_line;
extern int last_while_line;
extern int last_print_line;
extern int last_printf_line;
extern int last_id_line;
extern char *yytext;
extern FILE *yyin;

struct ASTNode {
    char *label;
    struct ASTNode *left, *mid, *right;
};

typedef struct Symbol {
    char *name;
    TypeKind type;
    int line;
} Symbol;

#define MAX_SYMBOLS 256

static Symbol symbols[MAX_SYMBOLS];
static int symbol_count = 0;
static int error_count = 0;

void yyerror(const char *s);
void reportSyntaxDetailAtLine(int line, const char *message);
void reportSemanticDetailAtLine(int line, const char *message);

ASTNode *makeNode(char *label, ASTNode *left, ASTNode *mid, ASTNode *right);
ASTNode *makeLeaf(char *label);
void printTree(ASTNode *node, int level);
void printLMD(ASTNode *node);
void printRMD(ASTNode *node);

SemVal makeSem(ASTNode *node, TypeKind type, int line);
SemVal makeLeafSem(char *label, TypeKind type, int line);
const char *typeName(TypeKind type);
int isNumeric(TypeKind type);
int isTruthType(TypeKind type);
int canAssign(TypeKind dest, TypeKind src);
int lookupSymbol(const char *name);
void declareSymbol(const char *name, TypeKind type, int line);
SemVal resolveIdentifier(const char *name, int line);
SemVal validateAssignment(const char *name, SemVal expr, int line);
void validateCondition(const char *keyword, SemVal expr, int line);
void validatePrint(SemVal expr, int line);
void validatePrintf(SemVal expr, int line);
SemVal checkBinaryNumeric(const char *op, SemVal left, SemVal right, int line);
SemVal checkModulo(SemVal left, SemVal right, int line);
SemVal checkLogical(const char *op, SemVal left, SemVal right, int line);
SemVal checkComparison(const char *op, SemVal left, SemVal right, int line);
SemVal checkEquality(const char *op, SemVal left, SemVal right, int line);
SemVal checkUnaryNot(SemVal expr, int line);
SemVal checkUnaryMinus(SemVal expr, int line);

ASTNode *makeNode(char *label, ASTNode *left, ASTNode *mid, ASTNode *right) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->label = strdup(label ? label : "MISSING_LABEL");
    node->left = left;
    node->mid = mid;
    node->right = right;
    return node;
}

ASTNode *makeLeaf(char *label) {
    return makeNode(label, NULL, NULL, NULL);
}

void printTree(ASTNode *node, int level) {
    int i;
    if (!node || !node->label) return;
    for (i = 0; i < level; i++) printf("  |__ ");
    printf("%s\n", node->label);
    printTree(node->left, level + 1);
    printTree(node->mid, level + 1);
    printTree(node->right, level + 1);
}

void printLMD(ASTNode *node) {
    if (!node || !node->label) return;
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
    if (!node || !node->label) return;
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

SemVal makeSem(ASTNode *node, TypeKind type, int line) {
    SemVal value;
    value.node = node;
    value.type = type;
    value.line = line;
    return value;
}

SemVal makeLeafSem(char *label, TypeKind type, int line) {
    return makeSem(makeLeaf(label), type, line);
}

const char *typeName(TypeKind type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_BOOL: return "bool";
        case TYPE_STRING: return "string";
        case TYPE_VOID: return "void";
        default: return "invalid";
    }
}

int isNumeric(TypeKind type) {
    return type == TYPE_INT || type == TYPE_FLOAT;
}

int isTruthType(TypeKind type) {
    return isNumeric(type) || type == TYPE_BOOL;
}

int canAssign(TypeKind dest, TypeKind src) {
    if (dest == TYPE_INVALID || src == TYPE_INVALID) return 1;
    if (dest == src) return 1;
    if (dest == TYPE_FLOAT && src == TYPE_INT) return 1;
    return 0;
}

void reportSyntaxDetailAtLine(int line, const char *message) {
    error_count++;
    printf("Syntax Error at line %d: %s\n", line, message);
}

void reportSemanticDetailAtLine(int line, const char *message) {
    error_count++;
    printf("Semantic Error at line %d: %s\n", line, message);
}

int lookupSymbol(const char *name) {
    int i;
    for (i = symbol_count - 1; i >= 0; i--) {
        if (strcmp(symbols[i].name, name) == 0) return i;
    }
    return -1;
}

void declareSymbol(const char *name, TypeKind type, int line) {
    char message[256];
    int index = lookupSymbol(name);
    if (index != -1) {
        snprintf(message, sizeof(message),
                 "redeclaration of '%s' (first declared at line %d)",
                 name, symbols[index].line);
        reportSemanticDetailAtLine(line, message);
        return;
    }
    if (symbol_count >= MAX_SYMBOLS) {
        reportSemanticDetailAtLine(line, "symbol table is full");
        return;
    }
    symbols[symbol_count].name = strdup(name);
    symbols[symbol_count].type = type;
    symbols[symbol_count].line = line;
    symbol_count++;
}

SemVal resolveIdentifier(const char *name, int line) {
    char message[256];
    int index = lookupSymbol(name);
    if (index == -1) {
        snprintf(message, sizeof(message), "use of undeclared identifier '%s'", name);
        reportSemanticDetailAtLine(line, message);
        return makeLeafSem((char *)name, TYPE_INVALID, line);
    }
    return makeLeafSem((char *)name, symbols[index].type, line);
}

SemVal validateAssignment(const char *name, SemVal expr, int line) {
    char message[256];
    int index = lookupSymbol(name);
    ASTNode *node = makeNode("Asgn(=)", makeLeaf((char *)name), expr.node, NULL);

    if (index == -1) {
        snprintf(message, sizeof(message), "assignment to undeclared identifier '%s'", name);
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    if (!canAssign(symbols[index].type, expr.type)) {
        snprintf(message, sizeof(message),
                 "cannot assign %s to %s variable '%s'",
                 typeName(expr.type), typeName(symbols[index].type), name);
        reportSemanticDetailAtLine(line, message);
    }

    return makeSem(node, symbols[index].type, line);
}

void validateCondition(const char *keyword, SemVal expr, int line) {
    char message[256];
    if (expr.type == TYPE_INVALID) return;
    if (!isTruthType(expr.type)) {
        snprintf(message, sizeof(message),
                 "%s condition must be numeric or boolean-like, got %s",
                 keyword, typeName(expr.type));
        reportSemanticDetailAtLine(line, message);
    }
}

void validatePrint(SemVal expr, int line) {
    char message[256];
    if (expr.type == TYPE_INVALID) return;
    if (expr.type == TYPE_VOID || expr.type == TYPE_STRING) {
        snprintf(message, sizeof(message),
                 "print expects a numeric expression, got %s",
                 typeName(expr.type));
        reportSemanticDetailAtLine(line, message);
    }
}

void validatePrintf(SemVal expr, int line) {
    char message[256];
    if (expr.type == TYPE_INVALID) return;
    if (expr.type != TYPE_STRING) {
        snprintf(message, sizeof(message),
                 "printf expects a string expression, got %s",
                 typeName(expr.type));
        reportSemanticDetailAtLine(line, message);
    }
}

SemVal checkBinaryNumeric(const char *op, SemVal left, SemVal right, int line) {
    char message[256];
    TypeKind result = TYPE_INVALID;
    ASTNode *node = makeNode((char *)op, left.node, right.node, NULL);

    if (left.type == TYPE_INVALID || right.type == TYPE_INVALID) {
        return makeSem(node, TYPE_INVALID, line);
    }

    if (!isNumeric(left.type) || !isNumeric(right.type)) {
        snprintf(message, sizeof(message),
                 "operator '%s' requires numeric operands, got %s and %s",
                 op, typeName(left.type), typeName(right.type));
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    result = (left.type == TYPE_FLOAT || right.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
    return makeSem(node, result, line);
}

SemVal checkModulo(SemVal left, SemVal right, int line) {
    char message[256];
    ASTNode *node = makeNode("%", left.node, right.node, NULL);

    if (left.type == TYPE_INVALID || right.type == TYPE_INVALID) {
        return makeSem(node, TYPE_INVALID, line);
    }

    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        snprintf(message, sizeof(message),
                 "operator '%%' requires int operands, got %s and %s",
                 typeName(left.type), typeName(right.type));
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    return makeSem(node, TYPE_INT, line);
}

SemVal checkLogical(const char *op, SemVal left, SemVal right, int line) {
    char message[256];
    ASTNode *node = makeNode((char *)op, left.node, right.node, NULL);

    if (left.type == TYPE_INVALID || right.type == TYPE_INVALID) {
        return makeSem(node, TYPE_INVALID, line);
    }

    if (!isTruthType(left.type) || !isTruthType(right.type)) {
        snprintf(message, sizeof(message),
                 "operator '%s' requires numeric or boolean-like operands, got %s and %s",
                 op, typeName(left.type), typeName(right.type));
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    return makeSem(node, TYPE_BOOL, line);
}

SemVal checkComparison(const char *op, SemVal left, SemVal right, int line) {
    char message[256];
    ASTNode *node = makeNode((char *)op, left.node, right.node, NULL);

    if (left.type == TYPE_INVALID || right.type == TYPE_INVALID) {
        return makeSem(node, TYPE_INVALID, line);
    }

    if (!isNumeric(left.type) || !isNumeric(right.type)) {
        snprintf(message, sizeof(message),
                 "operator '%s' requires numeric operands, got %s and %s",
                 op, typeName(left.type), typeName(right.type));
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    return makeSem(node, TYPE_BOOL, line);
}

SemVal checkEquality(const char *op, SemVal left, SemVal right, int line) {
    char message[256];
    ASTNode *node = makeNode((char *)op, left.node, right.node, NULL);
    int both_numeric = isNumeric(left.type) && isNumeric(right.type);
    int same_string = left.type == TYPE_STRING && right.type == TYPE_STRING;
    int same_bool = left.type == TYPE_BOOL && right.type == TYPE_BOOL;

    if (left.type == TYPE_INVALID || right.type == TYPE_INVALID) {
        return makeSem(node, TYPE_INVALID, line);
    }

    if (!both_numeric && !same_string && !same_bool) {
        snprintf(message, sizeof(message),
                 "operator '%s' cannot compare %s and %s",
                 op, typeName(left.type), typeName(right.type));
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    return makeSem(node, TYPE_BOOL, line);
}

SemVal checkUnaryNot(SemVal expr, int line) {
    char message[256];
    ASTNode *node = makeNode("!", expr.node, NULL, NULL);

    if (expr.type == TYPE_INVALID) {
        return makeSem(node, TYPE_INVALID, line);
    }

    if (!isTruthType(expr.type)) {
        snprintf(message, sizeof(message),
                 "operator '!' requires a numeric or boolean-like operand, got %s",
                 typeName(expr.type));
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    return makeSem(node, TYPE_BOOL, line);
}

SemVal checkUnaryMinus(SemVal expr, int line) {
    char message[256];
    ASTNode *node = makeNode("neg", expr.node, NULL, NULL);

    if (expr.type == TYPE_INVALID) {
        return makeSem(node, TYPE_INVALID, line);
    }

    if (!isNumeric(expr.type)) {
        snprintf(message, sizeof(message),
                 "unary '-' requires a numeric operand, got %s",
                 typeName(expr.type));
        reportSemanticDetailAtLine(line, message);
        return makeSem(node, TYPE_INVALID, line);
    }

    return makeSem(node, expr.type, line);
}
%}

%union {
    char *str;
    SemVal sem;
}

%token INT FLOAT IF ELSE WHILE PRINT PRINTF
%token <str> ID ICON FCON SCON
%token PLUS MINUS MUL DIV MOD EQ NEQ LT GT LEQ GEQ AND OR NOT
%token ASGN SEMI COMMA LP RP LC RC

%type <sem> Prog StmtList Stmt BareStmt Blk Decl Typ Asgn PrntStmt IfStmt WhlStmt Expr

%right ASGN
%nonassoc IF_NO_ELSE
%nonassoc ELSE
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GEQ
%left PLUS MINUS
%left MUL DIV MOD
%right NOT UMINUS

%start Prog

%%

Prog:
    StmtList {
        $$ = $1;
        if (error_count == 0) {
            printf("\n--- PARSE TREE ---\n");
            printTree($1.node, 0);
            printf("\n--- LEFTMOST DERIVATION (LMD) ---\n");
            printLMD($1.node);
            printf("\n\n--- RIGHTMOST DERIVATION (RMD) ---\n");
            printRMD($1.node);
            printf("\n\n");
        }
    }
    ;

StmtList:
      Stmt StmtList { $$ = makeSem(makeNode("StmtList", $1.node, $2.node, NULL), TYPE_VOID, $1.line); }
    | { $$ = makeSem(NULL, TYPE_VOID, err); }
    ;

Stmt:
      BareStmt { $$ = $1; }
    | Blk { $$ = $1; }
    | error SEMI {
          reportSyntaxDetailAtLine(err, "discarded invalid statement up to ';'");
          $$ = makeSem(NULL, TYPE_INVALID, err);
          yyerrok;
      }
    | error RC {
          reportSyntaxDetailAtLine(err, "discarded invalid statement before '}'");
          $$ = makeSem(NULL, TYPE_INVALID, err);
          yyerrok;
      }
    ;

BareStmt:
      Decl { $$ = $1; }
    | Asgn { $$ = $1; }
    | IfStmt { $$ = $1; }
    | WhlStmt { $$ = $1; }
    | PrntStmt { $$ = $1; }
    ;

Blk:
      LC StmtList RC { $$ = makeSem(makeNode("Block", $2.node, NULL, NULL), TYPE_VOID, err); }
    | LC StmtList error {
          reportSyntaxDetailAtLine(err, "missing '}' to close block");
          $$ = makeSem(makeNode("Block", $2.node, NULL, NULL), TYPE_VOID, err);
          yyerrok;
      }
    ;

Decl:
      Typ ID SEMI {
          declareSymbol($2, $1.type, last_id_line);
          $$ = makeSem(makeNode("Decl", $1.node, makeLeaf($2), NULL), TYPE_VOID, last_id_line);
      }
    | Typ ID error {
          reportSyntaxDetailAtLine(last_id_line, "missing ';' after declaration");
          declareSymbol($2, $1.type, last_id_line);
          $$ = makeSem(makeNode("Decl", $1.node, makeLeaf($2), NULL), TYPE_VOID, last_id_line);
          yyerrok;
      }
    | Typ error SEMI {
          reportSyntaxDetailAtLine(err, "missing identifier in declaration");
          $$ = makeSem(NULL, TYPE_INVALID, err);
          yyerrok;
      }
    ;

Typ:
      INT { $$ = makeSem(makeLeaf("int"), TYPE_INT, err); }
    | FLOAT { $$ = makeSem(makeLeaf("float"), TYPE_FLOAT, err); }
    ;

Asgn:
      ID ASGN Expr SEMI { $$ = validateAssignment($1, $3, last_id_line); }
    | ID ASGN Expr error {
          reportSyntaxDetailAtLine(last_id_line, "missing ';' after assignment");
          $$ = validateAssignment($1, $3, last_id_line);
          yyerrok;
      }
    | ID ASGN error SEMI {
          reportSyntaxDetailAtLine(last_id_line, "missing expression on right-hand side of assignment");
          $$ = makeSem(NULL, TYPE_INVALID, last_id_line);
          yyerrok;
      }
    | ID Expr SEMI {
          reportSyntaxDetailAtLine(last_id_line, "missing '=' in assignment");
          $$ = makeSem(NULL, TYPE_INVALID, last_id_line);
      }
    ;

PrntStmt:
      PRINT LP Expr RP SEMI {
          validatePrint($3, last_print_line);
          $$ = makeSem(makeNode("Print", $3.node, NULL, NULL), TYPE_VOID, last_print_line);
      }
    | PRINT Expr RP SEMI {
          reportSyntaxDetailAtLine(last_print_line, "missing '(' after 'print'");
          validatePrint($2, last_print_line);
          $$ = makeSem(makeNode("Print", $2.node, NULL, NULL), TYPE_VOID, last_print_line);
      }
    | PRINT LP Expr SEMI {
          reportSyntaxDetailAtLine(last_print_line, "missing ')' after print expression");
          validatePrint($3, last_print_line);
          $$ = makeSem(makeNode("Print", $3.node, NULL, NULL), TYPE_VOID, last_print_line);
      }
    | PRINT LP RP SEMI {
          reportSyntaxDetailAtLine(last_print_line, "missing expression inside print");
          $$ = makeSem(makeNode("Print", NULL, NULL, NULL), TYPE_VOID, last_print_line);
      }
    | PRINT LP Expr RP error {
          reportSyntaxDetailAtLine(last_print_line, "missing ';' after print statement");
          validatePrint($3, last_print_line);
          $$ = makeSem(makeNode("Print", $3.node, NULL, NULL), TYPE_VOID, last_print_line);
          yyerrok;
      }
    | PRINTF LP Expr RP SEMI {
          validatePrintf($3, last_printf_line);
          $$ = makeSem(makeNode("Printf", $3.node, NULL, NULL), TYPE_VOID, last_printf_line);
      }
    | PRINTF Expr RP SEMI {
          reportSyntaxDetailAtLine(last_printf_line, "missing '(' after 'printf'");
          validatePrintf($2, last_printf_line);
          $$ = makeSem(makeNode("Printf", $2.node, NULL, NULL), TYPE_VOID, last_printf_line);
      }
    | PRINTF LP Expr SEMI {
          reportSyntaxDetailAtLine(last_printf_line, "missing ')' after printf argument");
          validatePrintf($3, last_printf_line);
          $$ = makeSem(makeNode("Printf", $3.node, NULL, NULL), TYPE_VOID, last_printf_line);
      }
    | PRINTF LP RP SEMI {
          reportSyntaxDetailAtLine(last_printf_line, "missing argument inside printf");
          $$ = makeSem(makeNode("Printf", NULL, NULL, NULL), TYPE_VOID, last_printf_line);
      }
    | PRINTF LP Expr RP error {
          reportSyntaxDetailAtLine(last_printf_line, "missing ';' after printf statement");
          validatePrintf($3, last_printf_line);
          $$ = makeSem(makeNode("Printf", $3.node, NULL, NULL), TYPE_VOID, last_printf_line);
          yyerrok;
      }
    ;

IfStmt:
      IF LP Expr RP Blk %prec IF_NO_ELSE {
          validateCondition("if", $3, last_if_line);
          $$ = makeSem(makeNode("If", $3.node, $5.node, NULL), TYPE_VOID, last_if_line);
      }
    | IF LP Expr RP Blk ELSE Blk {
          validateCondition("if", $3, last_if_line);
          $$ = makeSem(makeNode("If-Else", $3.node, $5.node, $7.node), TYPE_VOID, last_if_line);
      }
    | IF LP RP Blk %prec IF_NO_ELSE {
          reportSyntaxDetailAtLine(last_if_line, "missing condition inside if");
          $$ = makeSem(makeNode("If", NULL, $4.node, NULL), TYPE_VOID, last_if_line);
      }
    | IF LP Expr Blk %prec IF_NO_ELSE {
          reportSyntaxDetailAtLine(last_if_line, "missing ')' after if condition");
          validateCondition("if", $3, last_if_line);
          $$ = makeSem(makeNode("If", $3.node, $4.node, NULL), TYPE_VOID, last_if_line);
      }
    | IF LP Expr Blk ELSE Blk {
          reportSyntaxDetailAtLine(last_if_line, "missing ')' after if condition");
          validateCondition("if", $3, last_if_line);
          $$ = makeSem(makeNode("If-Else", $3.node, $4.node, $6.node), TYPE_VOID, last_if_line);
      }
    | IF LP Expr RP BareStmt %prec IF_NO_ELSE {
          reportSyntaxDetailAtLine(last_if_line, "missing '{' and '}' around if body");
          validateCondition("if", $3, last_if_line);
          $$ = makeSem(makeNode("If", $3.node, makeNode("Block", $5.node, NULL, NULL), NULL), TYPE_VOID, last_if_line);
      }
    | IF LP Expr RP BareStmt ELSE Blk {
          reportSyntaxDetailAtLine(last_if_line, "missing '{' and '}' around if body");
          validateCondition("if", $3, last_if_line);
          $$ = makeSem(makeNode("If-Else", $3.node, makeNode("Block", $5.node, NULL, NULL), $7.node), TYPE_VOID, last_if_line);
      }
    | IF LP Expr RP Blk ELSE BareStmt {
          reportSyntaxDetailAtLine(last_if_line, "missing '{' and '}' around else body");
          validateCondition("if", $3, last_if_line);
          $$ = makeSem(makeNode("If-Else", $3.node, $5.node, makeNode("Block", $7.node, NULL, NULL)), TYPE_VOID, last_if_line);
      }
    | IF Expr RP Blk %prec IF_NO_ELSE {
          reportSyntaxDetailAtLine(last_if_line, "missing '(' after 'if'");
          validateCondition("if", $2, last_if_line);
          $$ = makeSem(makeNode("If", $2.node, $4.node, NULL), TYPE_VOID, last_if_line);
      }
    | IF Expr RP Blk ELSE Blk {
          reportSyntaxDetailAtLine(last_if_line, "missing '(' after 'if'");
          validateCondition("if", $2, last_if_line);
          $$ = makeSem(makeNode("If-Else", $2.node, $4.node, $6.node), TYPE_VOID, last_if_line);
      }
    ;

WhlStmt:
      WHILE LP Expr RP Blk {
          validateCondition("while", $3, last_while_line);
          $$ = makeSem(makeNode("While", $3.node, $5.node, NULL), TYPE_VOID, last_while_line);
      }
    | WHILE LP RP Blk {
          reportSyntaxDetailAtLine(last_while_line, "missing condition inside while");
          $$ = makeSem(makeNode("While", NULL, $4.node, NULL), TYPE_VOID, last_while_line);
      }
    | WHILE LP Expr Blk {
          reportSyntaxDetailAtLine(last_while_line, "missing ')' after while condition");
          validateCondition("while", $3, last_while_line);
          $$ = makeSem(makeNode("While", $3.node, $4.node, NULL), TYPE_VOID, last_while_line);
      }
    | WHILE LP Expr RP BareStmt {
          reportSyntaxDetailAtLine(last_while_line, "missing '{' and '}' around while body");
          validateCondition("while", $3, last_while_line);
          $$ = makeSem(makeNode("While", $3.node, makeNode("Block", $5.node, NULL, NULL), NULL), TYPE_VOID, last_while_line);
      }
    | WHILE Expr RP Blk {
          reportSyntaxDetailAtLine(last_while_line, "missing '(' after 'while'");
          validateCondition("while", $2, last_while_line);
          $$ = makeSem(makeNode("While", $2.node, $4.node, NULL), TYPE_VOID, last_while_line);
      }
    ;

Expr:
      Expr OR Expr { $$ = checkLogical("||", $1, $3, err); }
    | Expr AND Expr { $$ = checkLogical("&&", $1, $3, err); }
    | Expr EQ Expr { $$ = checkEquality("==", $1, $3, err); }
    | Expr NEQ Expr { $$ = checkEquality("!=", $1, $3, err); }
    | Expr LT Expr { $$ = checkComparison("<", $1, $3, err); }
    | Expr GT Expr { $$ = checkComparison(">", $1, $3, err); }
    | Expr LEQ Expr { $$ = checkComparison("<=", $1, $3, err); }
    | Expr GEQ Expr { $$ = checkComparison(">=", $1, $3, err); }
    | Expr PLUS Expr { $$ = checkBinaryNumeric("+", $1, $3, err); }
    | Expr MINUS Expr { $$ = checkBinaryNumeric("-", $1, $3, err); }
    | Expr MUL Expr { $$ = checkBinaryNumeric("*", $1, $3, err); }
    | Expr DIV Expr { $$ = checkBinaryNumeric("/", $1, $3, err); }
    | Expr MOD Expr { $$ = checkModulo($1, $3, err); }
    | NOT Expr { $$ = checkUnaryNot($2, err); }
    | MINUS Expr %prec UMINUS { $$ = checkUnaryMinus($2, err); }
    | LP Expr RP { $$ = $2; }
    | ID { $$ = resolveIdentifier($1, last_id_line); }
    | ICON { $$ = makeLeafSem($1, TYPE_INT, err); }
    | FCON { $$ = makeLeafSem($1, TYPE_FLOAT, err); }
    | SCON { $$ = makeLeafSem($1, TYPE_STRING, err); }
    ;

%%

void yyerror(const char *s) {
    const char *near = (yytext && yytext[0]) ? yytext : "EOF";
    error_count++;
    printf("Syntax Error at line %d near '%s'\n", err, near);
}

int main(void) {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error: Could not open file named 'input.txt'\n");
        return 1;
    }

    yyparse();

    if (error_count > 0) {
        printf("Parsing finished with errors.\n");
    }

    fclose(yyin);
    return 0;
}
