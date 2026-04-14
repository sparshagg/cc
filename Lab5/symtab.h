#ifndef SYMTAB_H
#define SYMTAB_H

typedef struct sym_record {
    char name[50];
    char type[20];
    int scope;
    int line;
    int is_initialized; // NEW: Tracks if it has a value!
    struct sym_record *next;
} sym_record;

void init_symtab();
unsigned int hash(char *str);
int insert_sym(char *name, char *type, int scope, int line);
sym_record* lookup_sym(char *name, int current_scope);
void delete_scope(int scope);
void print_symtab();

#endif