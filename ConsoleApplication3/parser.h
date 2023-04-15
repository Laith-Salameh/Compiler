/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WHILE = 258,
     IF = 259,
     ELSE = 260,
     INT = 261,
     FLOAT = 262,
     CHAR = 263,
     STRING = 264,
     BOOL = 265,
     BREAK = 266,
     CONTINUE = 267,
     RT = 268,
     NL = 269,
     TRUE = 270,
     FALSE = 271,
     EQ = 272,
     NEQ = 273,
     AND = 274,
     OR = 275,
     INTNUM = 276,
     FLOATNUM = 277,
     ID = 278,
     CHARCONST = 279,
     STRINGCONST = 280,
     CLASS = 281,
     IF_PREC = 282,
     OP = 283,
     eoe = 284
   };
#endif
/* Tokens.  */
#define WHILE 258
#define IF 259
#define ELSE 260
#define INT 261
#define FLOAT 262
#define CHAR 263
#define STRING 264
#define BOOL 265
#define BREAK 266
#define CONTINUE 267
#define RT 268
#define NL 269
#define TRUE 270
#define FALSE 271
#define EQ 272
#define NEQ 273
#define AND 274
#define OR 275
#define INTNUM 276
#define FLOATNUM 277
#define ID 278
#define CHARCONST 279
#define STRINGCONST 280
#define CLASS 281
#define IF_PREC 282
#define OP 283
#define eoe 284




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 23 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
typedef union YYSTYPE {
Class * tClass;
Small * tSmall;
Func * tfunc;
Type * ttype_specifier;
Decl_List * tdecl_list;
Param_Decl * tParam_decl;
Comp * tcomp;
Var_Decl * tvar_decl;
Var_Decl_List * tvar_decl_list;
Variable_Id * tvariable_id;
Stmt * tstmt;
Expr * texpr;
Expr_List * texprList;
int toperator;
Primary * tprimary;
Id * Tid;
Integer_value * tINTNUM;
Real_value * tFLOATNUM;
Char_value  * tCHARCONST;
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 118 "parser.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



