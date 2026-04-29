#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define TABLE_SIZE 100

sym_record* symtab[TABLE_SIZE];

void init_symtab() {
    for(int i = 0; i < TABLE_SIZE; i++) symtab[i] = NULL;
}

unsigned int hash(char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c; 
    return hash % TABLE_SIZE;
}

int insert_sym(char *name, char *type, int scope, int line) {
    unsigned int index = hash(name);
    sym_record *current = symtab[index];
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->scope == scope) {
            return 0; // Redeclaration error
        }
        current = current->next;
    }
    
    sym_record *new_node = (sym_record*)malloc(sizeof(sym_record));
    strcpy(new_node->name, name);
    strcpy(new_node->type, type);
    new_node->scope = scope;
    new_node->line = line;
    new_node->is_initialized = 0; 
    new_node->next = symtab[index];
    symtab[index] = new_node;
    return 1;
}

sym_record* lookup_sym(char *name, int current_scope) {
    unsigned int index = hash(name);
    sym_record *current = symtab[index];
    sym_record *best_match = NULL;
    int highest_scope = -1;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->scope <= current_scope && current->scope > highest_scope) {
                best_match = current;
                highest_scope = current->scope;
            }
        }
        current = current->next;
    }
    return best_match; 
}

void delete_scope(int scope) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        sym_record *current = symtab[i];
        sym_record *prev = NULL;
        while (current != NULL) {
            if (current->scope == scope) {
                if (prev == NULL) symtab[i] = current->next;
                else prev->next = current->next;
                sym_record *temp = current;
                current = current->next;
                free(temp);
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

void print_symtab() {
    printf("\n=== SEMANTIC SYMBOL TABLE ===\n");
    printf("%-15s | %-10s | %-6s | %-6s | %-12s\n", "Variable Name", "Data Type", "Scope", "Line", "Status");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        sym_record *current = symtab[i];
        while (current != NULL) {
            char status[20];
            strcpy(status, current->is_initialized ? "Initialized" : "Empty");
            printf("%-15s | %-10s | %-6d | %-6d | %-12s\n", current->name, current->type, current->scope, current->line, status);
            current = current->next;
        }
    }
    printf("================================================================\n\n");
}