/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     IF = 260,
     ELSE = 261,
     WHILE = 262,
     PRINT = 263,
     PRINTF = 264,
     ID = 265,
     ICON = 266,
     FCON = 267,
     SCON = 268,
     PLUS = 269,
     MINUS = 270,
     MUL = 271,
     DIV = 272,
     MOD = 273,
     EQ = 274,
     NEQ = 275,
     LT = 276,
     GT = 277,
     LEQ = 278,
     GEQ = 279,
     AND = 280,
     OR = 281,
     NOT = 282,
     ASGN = 283,
     SEMI = 284,
     COMMA = 285,
     LP = 286,
     RP = 287,
     LC = 288,
     RC = 289,
     IF_NO_ELSE = 290,
     UMINUS = 291
   };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define IF 260
#define ELSE 261
#define WHILE 262
#define PRINT 263
#define PRINTF 264
#define ID 265
#define ICON 266
#define FCON 267
#define SCON 268
#define PLUS 269
#define MINUS 270
#define MUL 271
#define DIV 272
#define MOD 273
#define EQ 274
#define NEQ 275
#define LT 276
#define GT 277
#define LEQ 278
#define GEQ 279
#define AND 280
#define OR 281
#define NOT 282
#define ASGN 283
#define SEMI 284
#define COMMA 285
#define LP 286
#define RP 287
#define LC 288
#define RC 289
#define IF_NO_ELSE 290
#define UMINUS 291




/* Copy the first part of user declarations.  */
#line 1 "par.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 394 "par.y"
{
    char *str;
    SemVal sem;
}
/* Line 193 of yacc.c.  */
#line 566 "par.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 579 "par.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   532

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  131

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    13,    16,    19,
      21,    23,    25,    27,    29,    33,    37,    41,    45,    49,
      51,    53,    58,    63,    68,    72,    78,    83,    88,    93,
      99,   105,   110,   115,   120,   126,   132,   140,   145,   150,
     157,   163,   171,   179,   184,   191,   197,   202,   207,   213,
     218,   222,   226,   230,   234,   238,   242,   246,   250,   254,
     258,   262,   266,   270,   273,   276,   280,   282,   284,   286
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      38,     0,    -1,    39,    -1,    40,    39,    -1,    -1,    41,
      -1,    42,    -1,     1,    29,    -1,     1,    34,    -1,    43,
      -1,    45,    -1,    47,    -1,    48,    -1,    46,    -1,    33,
      39,    34,    -1,    33,    39,     1,    -1,    44,    10,    29,
      -1,    44,    10,     1,    -1,    44,     1,    29,    -1,     3,
      -1,     4,    -1,    10,    28,    49,    29,    -1,    10,    28,
      49,     1,    -1,    10,    28,     1,    29,    -1,    10,    49,
      29,    -1,     8,    31,    49,    32,    29,    -1,     8,    49,
      32,    29,    -1,     8,    31,    49,    29,    -1,     8,    31,
      32,    29,    -1,     8,    31,    49,    32,     1,    -1,     9,
      31,    49,    32,    29,    -1,     9,    49,    32,    29,    -1,
       9,    31,    49,    29,    -1,     9,    31,    32,    29,    -1,
       9,    31,    49,    32,     1,    -1,     5,    31,    49,    32,
      42,    -1,     5,    31,    49,    32,    42,     6,    42,    -1,
       5,    31,    32,    42,    -1,     5,    31,    49,    42,    -1,
       5,    31,    49,    42,     6,    42,    -1,     5,    31,    49,
      32,    41,    -1,     5,    31,    49,    32,    41,     6,    42,
      -1,     5,    31,    49,    32,    42,     6,    41,    -1,     5,
      49,    32,    42,    -1,     5,    49,    32,    42,     6,    42,
      -1,     7,    31,    49,    32,    42,    -1,     7,    31,    32,
      42,    -1,     7,    31,    49,    42,    -1,     7,    31,    49,
      32,    41,    -1,     7,    49,    32,    42,    -1,    49,    26,
      49,    -1,    49,    25,    49,    -1,    49,    19,    49,    -1,
      49,    20,    49,    -1,    49,    21,    49,    -1,    49,    22,
      49,    -1,    49,    23,    49,    -1,    49,    24,    49,    -1,
      49,    14,    49,    -1,    49,    15,    49,    -1,    49,    16,
      49,    -1,    49,    17,    49,    -1,    49,    18,    49,    -1,
      27,    49,    -1,    15,    49,    -1,    31,    49,    32,    -1,
      10,    -1,    11,    -1,    12,    -1,    13,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   422,   422,   437,   438,   442,   443,   444,   449,   457,
     458,   459,   460,   461,   465,   466,   474,   478,   484,   492,
     493,   497,   498,   503,   508,   515,   519,   524,   529,   533,
     539,   543,   548,   553,   557,   566,   570,   574,   578,   583,
     588,   593,   598,   603,   608,   616,   620,   624,   629,   634,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "IF", "ELSE", "WHILE",
  "PRINT", "PRINTF", "ID", "ICON", "FCON", "SCON", "PLUS", "MINUS", "MUL",
  "DIV", "MOD", "EQ", "NEQ", "LT", "GT", "LEQ", "GEQ", "AND", "OR", "NOT",
  "ASGN", "SEMI", "COMMA", "LP", "RP", "LC", "RC", "IF_NO_ELSE", "UMINUS",
  "$accept", "Prog", "StmtList", "Stmt", "BareStmt", "Blk", "Decl", "Typ",
  "Asgn", "PrntStmt", "IfStmt", "WhlStmt", "Expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    40,    41,
      41,    41,    41,    41,    42,    42,    43,    43,    43,    44,
      44,    45,    45,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    48,    48,    48,    48,    48,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     4,     4,     4,     3,     5,     4,     4,     4,     5,
       5,     4,     4,     4,     5,     5,     7,     4,     4,     6,
       5,     7,     7,     4,     6,     5,     4,     4,     5,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    19,    20,     0,     0,     0,     0,     0,     0,
       0,     2,     0,     5,     6,     9,     0,    10,    13,    11,
      12,     7,     8,    66,    67,    68,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     3,     0,     0,    64,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    15,    14,    18,    17,
      16,    37,    65,    38,    58,    59,    60,    61,    62,    52,
      53,    54,    55,    56,    57,    51,    50,    43,    46,    65,
      47,    49,    28,    27,     0,    26,    33,    32,     0,    31,
      23,    22,    21,    65,    40,    35,     0,     0,    48,    45,
      29,    25,    34,    30,     0,     0,    39,    44,    41,    42,
      36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    30
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int16 yypact[] =
{
      20,    10,   -81,   -81,   232,   254,   260,   267,   225,    89,
       7,   -81,    79,   -81,   -81,   -81,     4,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   289,   289,   183,
     385,   190,   404,   196,   423,   219,   442,    90,   289,   480,
       3,   -81,   -81,   -21,     2,   -81,   -81,   -11,   307,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   -11,   -11,   327,   -11,    12,   347,    22,    38,
     366,    39,    45,   163,   461,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   166,    69,    55,    55,   -81,   -81,   -81,   508,
     508,    32,    32,    32,    32,   291,   496,    70,   -81,   166,
     -81,   -81,   -81,   -81,   110,   -81,   -81,   -81,   136,   -81,
     -81,   -81,   -81,   -81,    75,    98,   -11,   -11,   -81,   -81,
     -81,   -81,   -81,   -81,   -11,   166,   -81,   -81,   -81,   -81,
     -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,    -3,   -81,   -80,   -47,   -81,   -81,   -81,   -81,
     -81,   -81,     5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -66
static const yytype_int16 yytable[] =
{
      81,    83,   114,    79,    76,    43,    40,    41,    78,    42,
      32,    34,    36,    39,    44,    97,    98,   100,   101,   118,
      -4,     1,     9,     2,     3,     4,     0,     5,     6,     7,
       8,    80,    45,    46,    48,   115,    64,    77,    67,    21,
      70,   102,    73,    74,    22,   129,    49,    50,    51,    52,
      53,   105,   119,     9,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,   106,   109,   126,
     127,    51,    52,    53,   110,   116,   117,   128,   130,    -4,
       1,   124,     2,     3,     4,     0,     5,     6,     7,     8,
       1,    72,     2,     3,     4,     0,     5,     6,     7,     8,
      23,    24,    25,    26,   125,    27,     0,     0,     0,     0,
       0,   120,     9,    -4,     0,     0,     0,    28,     0,     0,
       0,    38,     9,    -4,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   122,     0,   121,
       0,     0,   -65,     0,     0,     0,     0,     0,     0,     0,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,     0,   111,   123,     0,     0,   -65,     2,
       3,     4,     0,     5,     6,     7,     8,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
       0,     0,   112,    23,    24,    25,    26,     0,    27,     9,
      23,    24,    25,    26,     0,    27,    23,    24,    25,    26,
      28,    27,     0,     0,    38,    47,     0,    28,     0,     0,
       0,    38,    63,    28,     0,     0,     0,    38,    66,    23,
      24,    25,    26,     0,    27,    23,    24,    25,    26,     0,
      27,     0,    23,    24,    25,    26,    28,    27,     0,     0,
      38,    69,    28,    37,     0,     0,    38,     0,     0,    28,
       0,     0,     0,    29,    23,    24,    25,    26,     0,    27,
      23,    24,    25,    26,     0,    27,     0,    23,    24,    25,
      26,    28,    27,     0,     0,    31,     0,    28,     0,     0,
       0,    33,     0,     0,    28,     0,     0,     0,    35,    23,
      24,    25,    26,     0,    27,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    28,     0,     0,     0,
      38,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     0,     0,     0,     0,     0,    82,
       9,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     0,     0,     0,     0,     0,    99,
       9,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     0,     0,   103,     0,     0,   104,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,     0,     0,   107,     0,     0,   108,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,     0,     0,     0,     0,     0,    62,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,     0,     0,     0,     0,     0,    65,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
       0,     0,     0,     0,     0,    68,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     0,
       0,     0,     0,     0,    71,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,     0,     0,
       0,     0,     0,   113,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,     0,     0,    75,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    49,    50,    51,    52,    53,     0,     0,    56,
      57,    58,    59
};

static const yytype_int8 yycheck[] =
{
      47,    48,    82,     1,     1,     1,     9,     0,    29,    12,
       5,     6,     7,     8,    10,    62,    63,    64,    65,    99,
       0,     1,    33,     3,     4,     5,    -1,     7,     8,     9,
      10,    29,    27,    28,    29,    82,    31,    34,    33,    29,
      35,    29,    37,    38,    34,   125,    14,    15,    16,    17,
      18,    29,    99,    33,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    29,    29,   116,
     117,    16,    17,    18,    29,     6,     6,   124,   125,     0,
       1,     6,     3,     4,     5,    -1,     7,     8,     9,    10,
       1,     1,     3,     4,     5,    -1,     7,     8,     9,    10,
      10,    11,    12,    13,     6,    15,    -1,    -1,    -1,    -1,
      -1,     1,    33,    34,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    31,    33,    34,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     1,    -1,    29,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,     1,    29,    -1,    -1,    32,     3,
       4,     5,    -1,     7,     8,     9,    10,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    29,    10,    11,    12,    13,    -1,    15,    33,
      10,    11,    12,    13,    -1,    15,    10,    11,    12,    13,
      27,    15,    -1,    -1,    31,    32,    -1,    27,    -1,    -1,
      -1,    31,    32,    27,    -1,    -1,    -1,    31,    32,    10,
      11,    12,    13,    -1,    15,    10,    11,    12,    13,    -1,
      15,    -1,    10,    11,    12,    13,    27,    15,    -1,    -1,
      31,    32,    27,    28,    -1,    -1,    31,    -1,    -1,    27,
      -1,    -1,    -1,    31,    10,    11,    12,    13,    -1,    15,
      10,    11,    12,    13,    -1,    15,    -1,    10,    11,    12,
      13,    27,    15,    -1,    -1,    31,    -1,    27,    -1,    -1,
      -1,    31,    -1,    -1,    27,    -1,    -1,    -1,    31,    10,
      11,    12,    13,    -1,    15,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    27,    -1,    -1,    -1,
      31,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,
      33,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,
      33,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    29,    -1,    -1,    32,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    -1,    -1,    32,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    32,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    32,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    32,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    32,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    32,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    29,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    14,    15,    16,    17,    18,    -1,    -1,    21,
      22,    23,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     7,     8,     9,    10,    33,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    29,    34,    10,    11,    12,    13,    15,    27,    31,
      49,    31,    49,    31,    49,    31,    49,    28,    31,    49,
      39,     0,    39,     1,    10,    49,    49,    32,    49,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    32,    32,    49,    32,    32,    49,    32,    32,
      49,    32,     1,    49,    49,    29,     1,    34,    29,     1,
      29,    42,    32,    42,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    42,    42,    32,
      42,    42,    29,    29,    32,    29,    29,    29,    32,    29,
      29,     1,    29,    32,    41,    42,     6,     6,    41,    42,
       1,    29,     1,    29,     6,     6,    42,    42,    42,    41,
      42
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 422 "par.y"
    {
        (yyval.sem) = (yyvsp[(1) - (1)].sem);
        if (error_count == 0) {
            printf("\n--- PARSE TREE ---\n");
            printTree((yyvsp[(1) - (1)].sem).node, 0);
            printf("\n--- LEFTMOST DERIVATION (LMD) ---\n");
            printLMD((yyvsp[(1) - (1)].sem).node);
            printf("\n\n--- RIGHTMOST DERIVATION (RMD) ---\n");
            printRMD((yyvsp[(1) - (1)].sem).node);
            printf("\n\n");
        }
    ;}
    break;

  case 3:
#line 437 "par.y"
    { (yyval.sem) = makeSem(makeNode("StmtList", (yyvsp[(1) - (2)].sem).node, (yyvsp[(2) - (2)].sem).node, NULL), TYPE_VOID, (yyvsp[(1) - (2)].sem).line); ;}
    break;

  case 4:
#line 438 "par.y"
    { (yyval.sem) = makeSem(NULL, TYPE_VOID, err); ;}
    break;

  case 5:
#line 442 "par.y"
    { (yyval.sem) = (yyvsp[(1) - (1)].sem); ;}
    break;

  case 6:
#line 443 "par.y"
    { (yyval.sem) = (yyvsp[(1) - (1)].sem); ;}
    break;

  case 7:
#line 444 "par.y"
    {
          reportSyntaxDetailAtLine(err, "discarded invalid statement up to ';'");
          (yyval.sem) = makeSem(NULL, TYPE_INVALID, err);
          yyerrok;
      ;}
    break;

  case 8:
#line 449 "par.y"
    {
          reportSyntaxDetailAtLine(err, "discarded invalid statement before '}'");
          (yyval.sem) = makeSem(NULL, TYPE_INVALID, err);
          yyerrok;
      ;}
    break;

  case 9:
#line 457 "par.y"
    { (yyval.sem) = (yyvsp[(1) - (1)].sem); ;}
    break;

  case 10:
#line 458 "par.y"
    { (yyval.sem) = (yyvsp[(1) - (1)].sem); ;}
    break;

  case 11:
#line 459 "par.y"
    { (yyval.sem) = (yyvsp[(1) - (1)].sem); ;}
    break;

  case 12:
#line 460 "par.y"
    { (yyval.sem) = (yyvsp[(1) - (1)].sem); ;}
    break;

  case 13:
#line 461 "par.y"
    { (yyval.sem) = (yyvsp[(1) - (1)].sem); ;}
    break;

  case 14:
#line 465 "par.y"
    { (yyval.sem) = makeSem(makeNode("Block", (yyvsp[(2) - (3)].sem).node, NULL, NULL), TYPE_VOID, err); ;}
    break;

  case 15:
#line 466 "par.y"
    {
          reportSyntaxDetailAtLine(err, "missing '}' to close block");
          (yyval.sem) = makeSem(makeNode("Block", (yyvsp[(2) - (3)].sem).node, NULL, NULL), TYPE_VOID, err);
          yyerrok;
      ;}
    break;

  case 16:
#line 474 "par.y"
    {
          declareSymbol((yyvsp[(2) - (3)].str), (yyvsp[(1) - (3)].sem).type, last_id_line);
          (yyval.sem) = makeSem(makeNode("Decl", (yyvsp[(1) - (3)].sem).node, makeLeaf((yyvsp[(2) - (3)].str)), NULL), TYPE_VOID, last_id_line);
      ;}
    break;

  case 17:
#line 478 "par.y"
    {
          reportSyntaxDetailAtLine(last_id_line, "missing ';' after declaration");
          declareSymbol((yyvsp[(2) - (3)].str), (yyvsp[(1) - (3)].sem).type, last_id_line);
          (yyval.sem) = makeSem(makeNode("Decl", (yyvsp[(1) - (3)].sem).node, makeLeaf((yyvsp[(2) - (3)].str)), NULL), TYPE_VOID, last_id_line);
          yyerrok;
      ;}
    break;

  case 18:
#line 484 "par.y"
    {
          reportSyntaxDetailAtLine(err, "missing identifier in declaration");
          (yyval.sem) = makeSem(NULL, TYPE_INVALID, err);
          yyerrok;
      ;}
    break;

  case 19:
#line 492 "par.y"
    { (yyval.sem) = makeSem(makeLeaf("int"), TYPE_INT, err); ;}
    break;

  case 20:
#line 493 "par.y"
    { (yyval.sem) = makeSem(makeLeaf("float"), TYPE_FLOAT, err); ;}
    break;

  case 21:
#line 497 "par.y"
    { (yyval.sem) = validateAssignment((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].sem), last_id_line); ;}
    break;

  case 22:
#line 498 "par.y"
    {
          reportSyntaxDetailAtLine(last_id_line, "missing ';' after assignment");
          (yyval.sem) = validateAssignment((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].sem), last_id_line);
          yyerrok;
      ;}
    break;

  case 23:
#line 503 "par.y"
    {
          reportSyntaxDetailAtLine(last_id_line, "missing expression on right-hand side of assignment");
          (yyval.sem) = makeSem(NULL, TYPE_INVALID, last_id_line);
          yyerrok;
      ;}
    break;

  case 24:
#line 508 "par.y"
    {
          reportSyntaxDetailAtLine(last_id_line, "missing '=' in assignment");
          (yyval.sem) = makeSem(NULL, TYPE_INVALID, last_id_line);
      ;}
    break;

  case 25:
#line 515 "par.y"
    {
          validatePrint((yyvsp[(3) - (5)].sem), last_print_line);
          (yyval.sem) = makeSem(makeNode("Print", (yyvsp[(3) - (5)].sem).node, NULL, NULL), TYPE_VOID, last_print_line);
      ;}
    break;

  case 26:
#line 519 "par.y"
    {
          reportSyntaxDetailAtLine(last_print_line, "missing '(' after 'print'");
          validatePrint((yyvsp[(2) - (4)].sem), last_print_line);
          (yyval.sem) = makeSem(makeNode("Print", (yyvsp[(2) - (4)].sem).node, NULL, NULL), TYPE_VOID, last_print_line);
      ;}
    break;

  case 27:
#line 524 "par.y"
    {
          reportSyntaxDetailAtLine(last_print_line, "missing ')' after print expression");
          validatePrint((yyvsp[(3) - (4)].sem), last_print_line);
          (yyval.sem) = makeSem(makeNode("Print", (yyvsp[(3) - (4)].sem).node, NULL, NULL), TYPE_VOID, last_print_line);
      ;}
    break;

  case 28:
#line 529 "par.y"
    {
          reportSyntaxDetailAtLine(last_print_line, "missing expression inside print");
          (yyval.sem) = makeSem(makeNode("Print", NULL, NULL, NULL), TYPE_VOID, last_print_line);
      ;}
    break;

  case 29:
#line 533 "par.y"
    {
          reportSyntaxDetailAtLine(last_print_line, "missing ';' after print statement");
          validatePrint((yyvsp[(3) - (5)].sem), last_print_line);
          (yyval.sem) = makeSem(makeNode("Print", (yyvsp[(3) - (5)].sem).node, NULL, NULL), TYPE_VOID, last_print_line);
          yyerrok;
      ;}
    break;

  case 30:
#line 539 "par.y"
    {
          validatePrintf((yyvsp[(3) - (5)].sem), last_printf_line);
          (yyval.sem) = makeSem(makeNode("Printf", (yyvsp[(3) - (5)].sem).node, NULL, NULL), TYPE_VOID, last_printf_line);
      ;}
    break;

  case 31:
#line 543 "par.y"
    {
          reportSyntaxDetailAtLine(last_printf_line, "missing '(' after 'printf'");
          validatePrintf((yyvsp[(2) - (4)].sem), last_printf_line);
          (yyval.sem) = makeSem(makeNode("Printf", (yyvsp[(2) - (4)].sem).node, NULL, NULL), TYPE_VOID, last_printf_line);
      ;}
    break;

  case 32:
#line 548 "par.y"
    {
          reportSyntaxDetailAtLine(last_printf_line, "missing ')' after printf argument");
          validatePrintf((yyvsp[(3) - (4)].sem), last_printf_line);
          (yyval.sem) = makeSem(makeNode("Printf", (yyvsp[(3) - (4)].sem).node, NULL, NULL), TYPE_VOID, last_printf_line);
      ;}
    break;

  case 33:
#line 553 "par.y"
    {
          reportSyntaxDetailAtLine(last_printf_line, "missing argument inside printf");
          (yyval.sem) = makeSem(makeNode("Printf", NULL, NULL, NULL), TYPE_VOID, last_printf_line);
      ;}
    break;

  case 34:
#line 557 "par.y"
    {
          reportSyntaxDetailAtLine(last_printf_line, "missing ';' after printf statement");
          validatePrintf((yyvsp[(3) - (5)].sem), last_printf_line);
          (yyval.sem) = makeSem(makeNode("Printf", (yyvsp[(3) - (5)].sem).node, NULL, NULL), TYPE_VOID, last_printf_line);
          yyerrok;
      ;}
    break;

  case 35:
#line 566 "par.y"
    {
          validateCondition("if", (yyvsp[(3) - (5)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If", (yyvsp[(3) - (5)].sem).node, (yyvsp[(5) - (5)].sem).node, NULL), TYPE_VOID, last_if_line);
      ;}
    break;

  case 36:
#line 570 "par.y"
    {
          validateCondition("if", (yyvsp[(3) - (7)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If-Else", (yyvsp[(3) - (7)].sem).node, (yyvsp[(5) - (7)].sem).node, (yyvsp[(7) - (7)].sem).node), TYPE_VOID, last_if_line);
      ;}
    break;

  case 37:
#line 574 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing condition inside if");
          (yyval.sem) = makeSem(makeNode("If", NULL, (yyvsp[(4) - (4)].sem).node, NULL), TYPE_VOID, last_if_line);
      ;}
    break;

  case 38:
#line 578 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing ')' after if condition");
          validateCondition("if", (yyvsp[(3) - (4)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If", (yyvsp[(3) - (4)].sem).node, (yyvsp[(4) - (4)].sem).node, NULL), TYPE_VOID, last_if_line);
      ;}
    break;

  case 39:
#line 583 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing ')' after if condition");
          validateCondition("if", (yyvsp[(3) - (6)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If-Else", (yyvsp[(3) - (6)].sem).node, (yyvsp[(4) - (6)].sem).node, (yyvsp[(6) - (6)].sem).node), TYPE_VOID, last_if_line);
      ;}
    break;

  case 40:
#line 588 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing '{' and '}' around if body");
          validateCondition("if", (yyvsp[(3) - (5)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If", (yyvsp[(3) - (5)].sem).node, makeNode("Block", (yyvsp[(5) - (5)].sem).node, NULL, NULL), NULL), TYPE_VOID, last_if_line);
      ;}
    break;

  case 41:
#line 593 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing '{' and '}' around if body");
          validateCondition("if", (yyvsp[(3) - (7)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If-Else", (yyvsp[(3) - (7)].sem).node, makeNode("Block", (yyvsp[(5) - (7)].sem).node, NULL, NULL), (yyvsp[(7) - (7)].sem).node), TYPE_VOID, last_if_line);
      ;}
    break;

  case 42:
#line 598 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing '{' and '}' around else body");
          validateCondition("if", (yyvsp[(3) - (7)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If-Else", (yyvsp[(3) - (7)].sem).node, (yyvsp[(5) - (7)].sem).node, makeNode("Block", (yyvsp[(7) - (7)].sem).node, NULL, NULL)), TYPE_VOID, last_if_line);
      ;}
    break;

  case 43:
#line 603 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing '(' after 'if'");
          validateCondition("if", (yyvsp[(2) - (4)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If", (yyvsp[(2) - (4)].sem).node, (yyvsp[(4) - (4)].sem).node, NULL), TYPE_VOID, last_if_line);
      ;}
    break;

  case 44:
#line 608 "par.y"
    {
          reportSyntaxDetailAtLine(last_if_line, "missing '(' after 'if'");
          validateCondition("if", (yyvsp[(2) - (6)].sem), last_if_line);
          (yyval.sem) = makeSem(makeNode("If-Else", (yyvsp[(2) - (6)].sem).node, (yyvsp[(4) - (6)].sem).node, (yyvsp[(6) - (6)].sem).node), TYPE_VOID, last_if_line);
      ;}
    break;

  case 45:
#line 616 "par.y"
    {
          validateCondition("while", (yyvsp[(3) - (5)].sem), last_while_line);
          (yyval.sem) = makeSem(makeNode("While", (yyvsp[(3) - (5)].sem).node, (yyvsp[(5) - (5)].sem).node, NULL), TYPE_VOID, last_while_line);
      ;}
    break;

  case 46:
#line 620 "par.y"
    {
          reportSyntaxDetailAtLine(last_while_line, "missing condition inside while");
          (yyval.sem) = makeSem(makeNode("While", NULL, (yyvsp[(4) - (4)].sem).node, NULL), TYPE_VOID, last_while_line);
      ;}
    break;

  case 47:
#line 624 "par.y"
    {
          reportSyntaxDetailAtLine(last_while_line, "missing ')' after while condition");
          validateCondition("while", (yyvsp[(3) - (4)].sem), last_while_line);
          (yyval.sem) = makeSem(makeNode("While", (yyvsp[(3) - (4)].sem).node, (yyvsp[(4) - (4)].sem).node, NULL), TYPE_VOID, last_while_line);
      ;}
    break;

  case 48:
#line 629 "par.y"
    {
          reportSyntaxDetailAtLine(last_while_line, "missing '{' and '}' around while body");
          validateCondition("while", (yyvsp[(3) - (5)].sem), last_while_line);
          (yyval.sem) = makeSem(makeNode("While", (yyvsp[(3) - (5)].sem).node, makeNode("Block", (yyvsp[(5) - (5)].sem).node, NULL, NULL), NULL), TYPE_VOID, last_while_line);
      ;}
    break;

  case 49:
#line 634 "par.y"
    {
          reportSyntaxDetailAtLine(last_while_line, "missing '(' after 'while'");
          validateCondition("while", (yyvsp[(2) - (4)].sem), last_while_line);
          (yyval.sem) = makeSem(makeNode("While", (yyvsp[(2) - (4)].sem).node, (yyvsp[(4) - (4)].sem).node, NULL), TYPE_VOID, last_while_line);
      ;}
    break;

  case 50:
#line 642 "par.y"
    { (yyval.sem) = checkLogical("||", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 51:
#line 643 "par.y"
    { (yyval.sem) = checkLogical("&&", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 52:
#line 644 "par.y"
    { (yyval.sem) = checkEquality("==", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 53:
#line 645 "par.y"
    { (yyval.sem) = checkEquality("!=", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 54:
#line 646 "par.y"
    { (yyval.sem) = checkComparison("<", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 55:
#line 647 "par.y"
    { (yyval.sem) = checkComparison(">", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 56:
#line 648 "par.y"
    { (yyval.sem) = checkComparison("<=", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 57:
#line 649 "par.y"
    { (yyval.sem) = checkComparison(">=", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 58:
#line 650 "par.y"
    { (yyval.sem) = checkBinaryNumeric("+", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 59:
#line 651 "par.y"
    { (yyval.sem) = checkBinaryNumeric("-", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 60:
#line 652 "par.y"
    { (yyval.sem) = checkBinaryNumeric("*", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 61:
#line 653 "par.y"
    { (yyval.sem) = checkBinaryNumeric("/", (yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 62:
#line 654 "par.y"
    { (yyval.sem) = checkModulo((yyvsp[(1) - (3)].sem), (yyvsp[(3) - (3)].sem), err); ;}
    break;

  case 63:
#line 655 "par.y"
    { (yyval.sem) = checkUnaryNot((yyvsp[(2) - (2)].sem), err); ;}
    break;

  case 64:
#line 656 "par.y"
    { (yyval.sem) = checkUnaryMinus((yyvsp[(2) - (2)].sem), err); ;}
    break;

  case 65:
#line 657 "par.y"
    { (yyval.sem) = (yyvsp[(2) - (3)].sem); ;}
    break;

  case 66:
#line 658 "par.y"
    { (yyval.sem) = resolveIdentifier((yyvsp[(1) - (1)].str), last_id_line); ;}
    break;

  case 67:
#line 659 "par.y"
    { (yyval.sem) = makeLeafSem((yyvsp[(1) - (1)].str), TYPE_INT, err); ;}
    break;

  case 68:
#line 660 "par.y"
    { (yyval.sem) = makeLeafSem((yyvsp[(1) - (1)].str), TYPE_FLOAT, err); ;}
    break;

  case 69:
#line 661 "par.y"
    { (yyval.sem) = makeLeafSem((yyvsp[(1) - (1)].str), TYPE_STRING, err); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2447 "par.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 664 "par.y"


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

