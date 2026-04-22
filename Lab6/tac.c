#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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