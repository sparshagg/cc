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
     ID = 264,
     ICON = 265,
     FCON = 266,
     PLUS = 267,
     MINUS = 268,
     MUL = 269,
     DIV = 270,
     MOD = 271,
     EQ = 272,
     NEQ = 273,
     LT = 274,
     GT = 275,
     LEQ = 276,
     GEQ = 277,
     AND = 278,
     OR = 279,
     NOT = 280,
     ASGN = 281,
     SEMI = 282,
     COMMA = 283,
     LP = 284,
     RP = 285,
     LC = 286,
     RC = 287
   };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define IF 260
#define ELSE 261
#define WHILE 262
#define PRINT 263
#define ID 264
#define ICON 265
#define FCON 266
#define PLUS 267
#define MINUS 268
#define MUL 269
#define DIV 270
#define MOD 271
#define EQ 272
#define NEQ 273
#define LT 274
#define GT 275
#define LEQ 276
#define GEQ 277
#define AND 278
#define OR 279
#define NOT 280
#define ASGN 281
#define SEMI 282
#define COMMA 283
#define LP 284
#define RP 285
#define LC 286
#define RC 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 48 "par.y"
{ char *s; struct N *n; }
/* Line 1529 of yacc.c.  */
#line 115 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

