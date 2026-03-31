/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 394 "par.y"
{
    char *str;
    SemVal sem;
}
/* Line 1529 of yacc.c.  */
#line 126 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

