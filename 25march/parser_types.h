#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

typedef struct ASTNode ASTNode;

typedef enum {
    TYPE_INVALID,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_VOID
} TypeKind;

typedef struct SemVal {
    ASTNode *node;
    TypeKind type;
    int line;
} SemVal;

#endif
