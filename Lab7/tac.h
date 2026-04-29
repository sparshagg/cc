#ifndef TAC_H
#define TAC_H

// Forward declaration of the AST Node struct defined in par.y
typedef struct N N;

typedef struct quad {
    char op[20];
    char arg1[20];
    char arg2[20];
    char res[20];
} quad;

void init_tac();
char* new_temp();
char* new_label();
void emit(char *op, char *arg1, char *arg2, char *res);
char* generate_tac(N *node);
void print_quadruples();

// === PHASE V: OPTIMIZATION & CODE GEN ===
void optimize_tac();
void print_optimized_quadruples();
void generate_assembly();

#endif