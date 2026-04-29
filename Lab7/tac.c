#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Redeclaring the basic struct here so tac.c knows how to traverse it
typedef struct N {
    char *l;
    char *type; 
    struct N *L, *M, *R;
} N;

#include "tac.h"

#define MAX_QUAD 1000

quad quad_array[MAX_QUAD];
int quad_idx = 0;
int temp_cnt = 0;
int label_cnt = 0;

void init_tac() {
    quad_idx = 0;
    temp_cnt = 0;
    label_cnt = 0;
}

char* new_temp() {
    char *t = (char*)malloc(10);
    sprintf(t, "t%d", temp_cnt++);
    return t;
}

char* new_label() {
    char *l = (char*)malloc(10);
    sprintf(l, "L%d", label_cnt++);
    return l;
}

void emit(char *op, char *arg1, char *arg2, char *res) {
    if(quad_idx >= MAX_QUAD) return;
    strcpy(quad_array[quad_idx].op, op);
    strcpy(quad_array[quad_idx].arg1, arg1 ? arg1 : "-");
    strcpy(quad_array[quad_idx].arg2, arg2 ? arg2 : "-");
    strcpy(quad_array[quad_idx].res, res ? res : "-");
    quad_idx++;
}

char* generate_tac(N *node) {
    if (!node) return "-";
    
    if (!node->L && !node->M && !node->R) {
        return node->l;
    }

    char *op = node->l;

    if (strcmp(op, "SL") == 0) {
        generate_tac(node->L);
        generate_tac(node->M);
        return "-";
    }
    if (strcmp(op, "Blk") == 0) {
        generate_tac(node->L);
        return "-";
    }

    if (strcmp(op, "Decl") == 0) return "-";

    if (strcmp(op, "Asgn") == 0) {
        char *arg1 = generate_tac(node->M); 
        char *res = generate_tac(node->L);  
        emit("=", arg1, "-", res);
        return "-";
    }

    if (strcmp(op, "Prnt") == 0) {
        char *arg1 = generate_tac(node->L);
        emit("print", arg1, "-", "-");
        return "-";
    }

    if (strcmp(op, "Whl") == 0) {
        char *L_start = new_label();
        char *L_end = new_label();
        
        emit("LABEL", "-", "-", L_start);      
        char *cond = generate_tac(node->L);    
        emit("IFFALSE", cond, "-", L_end);     
        
        generate_tac(node->M);                 
        emit("GOTO", "-", "-", L_start);       
        
        emit("LABEL", "-", "-", L_end);        
        return "-";
    }

    if (strcmp(op, "IfElse") == 0) {
        char *L_false = new_label();
        char *L_end = new_label();
        
        char *cond = generate_tac(node->L);
        emit("IFFALSE", cond, "-", L_false);   
        
        generate_tac(node->M);                 
        emit("GOTO", "-", "-", L_end);         
        
        emit("LABEL", "-", "-", L_false);      
        generate_tac(node->R);                 
        
        emit("LABEL", "-", "-", L_end);        
        return "-";
    }

    if (strcmp(op, "If") == 0) {
        char *L_end = new_label();
        
        char *cond = generate_tac(node->L);
        emit("IFFALSE", cond, "-", L_end);
        
        generate_tac(node->M);
        emit("LABEL", "-", "-", L_end);
        return "-";
    }

    char *arg1 = generate_tac(node->L);
    char *arg2 = generate_tac(node->M);
    char *res = new_temp();
    emit(op, arg1, arg2, res);
    
    return res; 
}

void print_quadruples() {
    printf("\n=== THREE-ADDRESS CODE (QUADRUPLES) ===\n");
    printf("%-5s | %-10s | %-10s | %-10s | %-10s\n", "Idx", "Operator", "Arg 1", "Arg 2", "Result");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < quad_idx; i++) {
        if (strcmp(quad_array[i].op, "LABEL") == 0) {
            printf("\n%s:\n", quad_array[i].res);
        } else {
            printf("%-5d | %-10s | %-10s | %-10s | %-10s\n", 
                i, quad_array[i].op, quad_array[i].arg1, quad_array[i].arg2, quad_array[i].res);
        }
    }
    printf("==========================================================\n\n");
}

// =====================================================================
// PHASE V: OPTIMIZATION & ASSEMBLY GENERATION
// =====================================================================

// Helper function to check if a string is a pure number
int is_num(char *str) {
    if(!str || strcmp(str, "-") == 0) return 0;
    int i = 0;
    if(str[0] == '-') i++;
    for(; str[i]; i++) {
        if(!isdigit(str[i]) && str[i] != '.') return 0;
    }
    return 1;
}

// 1. OPTIMIZATION ENGINE (Constant Folding)
void optimize_tac() {
    for(int i=0; i<quad_idx; i++) {
        if (is_num(quad_array[i].arg1) && is_num(quad_array[i].arg2)) {
            float v1 = atof(quad_array[i].arg1);
            float v2 = atof(quad_array[i].arg2);
            float res_val = 0;
            int optimizable = 1;
            
            if(strcmp(quad_array[i].op, "+") == 0) res_val = v1 + v2;
            else if(strcmp(quad_array[i].op, "-") == 0) res_val = v1 - v2;
            else if(strcmp(quad_array[i].op, "*") == 0) res_val = v1 * v2;
            else if(strcmp(quad_array[i].op, "/") == 0) {
                if(v2 != 0) res_val = v1 / v2; else optimizable = 0; 
            } else optimizable = 0;
            
            if(optimizable) {
                strcpy(quad_array[i].op, "=");
                if(res_val == (int)res_val) sprintf(quad_array[i].arg1, "%d", (int)res_val);
                else sprintf(quad_array[i].arg1, "%.2f", res_val);
                strcpy(quad_array[i].arg2, "-");
            }
        }
    }
}

void print_optimized_quadruples() {
    printf("\n=== OPTIMIZED THREE-ADDRESS CODE (CONSTANT FOLDING) ===\n");
    printf("%-5s | %-10s | %-10s | %-10s | %-10s\n", "Idx", "Operator", "Arg 1", "Arg 2", "Result");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < quad_idx; i++) {
        if (strcmp(quad_array[i].op, "LABEL") == 0) printf("\n%s:\n", quad_array[i].res);
        else printf("%-5d | %-10s | %-10s | %-10s | %-10s\n", i, quad_array[i].op, quad_array[i].arg1, quad_array[i].arg2, quad_array[i].res);
    }
    printf("==========================================================\n\n");
}

// 2. TARGET CODE GENERATOR (MIPS Pseudo-Assembly)
void generate_assembly() {
    printf("\n=== TARGET CODE (MIPS PSEUDO-ASSEMBLY) ===\n");
    printf(".data\n");
    printf("    # Variables mapped dynamically to RAM\n\n");
    printf(".text\n");
    printf("MAIN:\n");
    for(int i=0; i<quad_idx; i++) {
        char *op = quad_array[i].op;
        char *arg1 = quad_array[i].arg1;
        char *arg2 = quad_array[i].arg2;
        char *res = quad_array[i].res;
        
        if (strcmp(op, "LABEL") == 0) {
            printf("\n%s:\n", res);
        } else if (strcmp(op, "=") == 0) {
            printf("    LOAD R1, %s\n", arg1);
            printf("    STORE R1, %s\n", res);
        } else if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
            printf("    LOAD R1, %s\n", arg1);
            printf("    LOAD R2, %s\n", arg2);
            if (strcmp(op, "+")==0) printf("    ADD R3, R1, R2\n");
            if (strcmp(op, "-")==0) printf("    SUB R3, R1, R2\n");
            if (strcmp(op, "*")==0) printf("    MUL R3, R1, R2\n");
            if (strcmp(op, "/")==0) printf("    DIV R3, R1, R2\n");
            printf("    STORE R3, %s\n", res);
        } else if (strcmp(op, "IFFALSE") == 0) {
            printf("    LOAD R1, %s\n", arg1);
            printf("    BEQZ R1, %s    # Branch if Zero (False)\n", res);
        } else if (strcmp(op, "GOTO") == 0) {
            printf("    JUMP %s\n", res);
        } else if (strcmp(op, "print") == 0) {
            printf("    LOAD R1, %s\n", arg1);
            printf("    PRINT R1\n");
        } else if (strcmp(op, "<")==0 || strcmp(op, ">")==0 || strcmp(op, "==")==0 || strcmp(op, "!=")==0) {
            printf("    LOAD R1, %s\n", arg1);
            printf("    LOAD R2, %s\n", arg2);
            if(strcmp(op, "<")==0) printf("    SLT R3, R1, R2\n");
            if(strcmp(op, ">")==0) printf("    SGT R3, R1, R2\n");
            if(strcmp(op, "==")==0) printf("    SEQ R3, R1, R2\n");
            if(strcmp(op, "!=")==0) printf("    SNE R3, R1, R2\n");
            printf("    STORE R3, %s\n", res);
        } else if (strcmp(op, "&&")==0 || strcmp(op, "||")==0) {
            printf("    LOAD R1, %s\n", arg1);
            printf("    LOAD R2, %s\n", arg2);
            if(strcmp(op, "&&")==0) printf("    AND R3, R1, R2\n");
            if(strcmp(op, "||")==0) printf("    OR R3, R1, R2\n");
            printf("    STORE R3, %s\n", res);
        }
    }
    printf("    HALT\n");
    printf("==========================================\n\n");
}