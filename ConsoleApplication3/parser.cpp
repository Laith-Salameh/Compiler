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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

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




/* Copy the first part of user declarations.  */
#line 1 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"

	#include "AST.h"
	#include <iostream>
	using std::cout;
	using std::endl;
	extern int yylex();
	extern int line,col;
	int yyerror(const char *s1);
	extern int yydebug;
	Class * root;
	extern char* yytext;
	SymbolTable * symbolTable = new SymbolTable();
	int current_type;
	int current_kind = 2;
	int last_func = 0 ;
	int whileLabel = 0;
	int ifLabel = 0;
	int ifElseLabel = 0;
	int forLabel=0;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
/* Line 196 of yacc.c.  */
#line 187 "parser.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 199 "parser.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   384

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  25
/* YYNRULES -- Number of rules. */
#define YYNRULES  70
/* YYNRULES -- Number of states. */
#define YYNSTATES  123

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,     2,     2,    35,     2,     2,
      40,    41,    33,    32,    42,    31,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      29,    28,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25,    26,    27,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     5,    13,    14,    17,    20,    21,
      31,    32,    41,    43,    45,    47,    49,    51,    52,    54,
      58,    60,    63,    66,    69,    70,    74,    78,    80,    82,
      86,    88,    90,    93,    96,    99,   103,   106,   114,   126,
     134,   138,   140,   144,   147,   151,   154,   157,   162,   163,
     165,   167,   171,   173,   175,   177,   179,   181,   183,   185,
     187,   189,   191,   193,   195,   197,   199,   201,   203,   205,
     207
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      46,     0,    -1,    -1,    -1,    26,    47,    23,    48,    38,
      49,    39,    -1,    -1,    49,    50,    -1,    49,    58,    -1,
      -1,    53,    23,    51,    40,    54,    41,    38,    57,    39,
      -1,    -1,    23,    52,    40,    54,    41,    38,    57,    39,
      -1,     6,    -1,     7,    -1,    10,    -1,     8,    -1,     9,
      -1,    -1,    55,    -1,    55,    42,    56,    -1,    56,    -1,
      53,    23,    -1,    57,    58,    -1,    57,    61,    -1,    -1,
      53,    59,    43,    -1,    59,    42,    60,    -1,    60,    -1,
      23,    -1,    23,    28,    65,    -1,    62,    -1,    63,    -1,
      11,    43,    -1,    64,    43,    -1,    12,    43,    -1,    13,
      65,    43,    -1,    65,    43,    -1,     4,    40,    65,    41,
      38,    57,    39,    -1,     4,    40,    65,    41,    38,    57,
      39,     5,    38,    57,    39,    -1,     3,    40,    65,    41,
      38,    57,    39,    -1,    23,    28,    65,    -1,    69,    -1,
      65,    68,    65,    -1,    44,    65,    -1,    40,    65,    41,
      -1,    31,    65,    -1,    32,    65,    -1,    23,    40,    66,
      41,    -1,    -1,    67,    -1,    65,    -1,    67,    42,    65,
      -1,    32,    -1,    31,    -1,    33,    -1,    34,    -1,    35,
      -1,    30,    -1,    29,    -1,    17,    -1,    19,    -1,    20,
      -1,    18,    -1,    21,    -1,    22,    -1,    24,    -1,    25,
      -1,    23,    -1,    15,    -1,    16,    -1,    14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    97,    97,   100,    96,   111,   114,   118,   124,   124,
     137,   137,   150,   156,   161,   166,   171,   180,   183,   189,
     194,   201,   208,   212,   217,   223,   230,   235,   241,   246,
     253,   257,   261,   265,   269,   273,   278,   284,   288,   294,
     300,   307,   311,   315,   319,   323,   327,   331,   339,   342,
     348,   352,   359,   363,   367,   371,   375,   379,   383,   387,
     391,   395,   399,   405,   409,   413,   417,   421,   426,   430,
     434
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE", "IF", "ELSE", "INT", "FLOAT",
  "CHAR", "STRING", "BOOL", "BREAK", "CONTINUE", "RT", "NL", "TRUE",
  "FALSE", "EQ", "NEQ", "AND", "OR", "INTNUM", "FLOATNUM", "ID",
  "CHARCONST", "STRINGCONST", "CLASS", "IF_PREC", "'='", "'<'", "'>'",
  "'-'", "'+'", "'*'", "'/'", "'%'", "OP", "eoe", "'{'", "'}'", "'('",
  "')'", "','", "';'", "'!'", "$accept", "Class", "@1", "@2", "Small",
  "func", "@3", "@4", "type_specifier", "decl_list", "decl_list_e",
  "Param_decl", "comp", "var_decl", "var_decl_list", "variable_id", "stmt",
  "cond_stmt", "while_stmt", "assignStmt", "expr", "exprList",
  "exprList_e", "operator", "primary", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    61,    60,
      62,    45,    43,    42,    47,    37,   283,   284,   123,   125,
      40,    41,    44,    59,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    45,    47,    48,    46,    49,    49,    49,    51,    50,
      52,    50,    53,    53,    53,    53,    53,    54,    54,    55,
      55,    56,    57,    57,    57,    58,    59,    59,    60,    60,
      61,    61,    61,    61,    61,    61,    61,    62,    62,    63,
      64,    65,    65,    65,    65,    65,    65,    65,    66,    66,
      67,    67,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    69,    69,    69,    69,    69,
      69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,     7,     0,     2,     2,     0,     9,
       0,     8,     1,     1,     1,     1,     1,     0,     1,     3,
       1,     2,     2,     2,     0,     3,     3,     1,     1,     3,
       1,     1,     2,     2,     2,     3,     2,     7,    11,     7,
       3,     1,     3,     2,     3,     2,     2,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     2,     0,     0,     1,     3,     0,     5,     0,    12,
      13,    15,    16,    14,    10,     4,     6,     0,     7,     0,
      28,     0,    27,    17,     0,     0,     0,    25,     0,     0,
      18,    20,    70,    68,    69,    63,    64,    67,    65,    66,
       0,     0,     0,     0,    29,    41,    17,    28,    26,    21,
       0,     0,    48,    45,    46,     0,    43,    59,    62,    60,
      61,    58,    57,    53,    52,    54,    55,    56,     0,     0,
      24,    19,    50,     0,    49,    44,    42,     0,     0,    47,
       0,    24,     0,     0,     0,     0,     0,    67,    11,     0,
      22,    23,    30,    31,     0,     0,    51,     0,     0,     0,
      32,    34,     0,     0,    33,    36,     9,     0,     0,    35,
      40,     0,     0,    24,    24,     0,     0,    39,    37,     0,
      24,     0,    38
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,     3,     6,     8,    16,    25,    19,    89,    29,
      30,    31,    78,    90,    21,    22,    91,    92,    93,    94,
      95,    73,    74,    68,    45
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const short int yypact[] =
{
     -22,   -81,    13,    -2,   -81,   -81,   -16,   -81,     0,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,     1,   -81,   -15,
     -26,   -31,   -81,    51,   257,   -14,     4,   -81,     6,   -11,
     -10,   -81,   -81,   -81,   -81,   -81,   -81,    -9,   -81,   -81,
     257,   257,   257,   257,   349,   -81,    51,     7,   -81,   -81,
      -1,    51,   257,   -81,   -81,    35,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   257,    -5,
     -81,   -81,   349,     5,    -4,   -81,   -81,     3,    74,   -81,
     257,   -81,     2,     9,     8,    20,   257,   -25,   -81,     4,
     -81,   -81,   -81,   -81,    28,   273,   349,   113,   257,   257,
     -81,   -81,   292,   257,   -81,   -81,   -81,   311,   330,   -81,
     349,    12,    34,   -81,   -81,   152,   191,   -81,    40,    53,
     -81,   230,   -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,    -3,    27,
     -81,    41,   -80,    39,   -81,    67,   -81,   -81,   -81,   -81,
     -24,   -81,   -81,   -81,   -81
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -9
static const yysigned_char yytable[] =
{
      44,    97,    24,   103,     1,    17,     9,    10,    11,    12,
      13,    26,    27,     4,    -8,    52,    53,    54,    55,    56,
      28,     5,     7,    14,    20,    23,    46,    47,    72,    49,
      50,    52,    51,   115,   116,    24,    77,    70,    80,    15,
     121,    81,    98,    28,    76,   119,    79,    18,    28,    99,
     113,   100,    57,    58,    59,    60,    96,     9,    10,    11,
      12,    13,   102,   101,    61,    62,    63,    64,    65,    66,
      67,   104,   114,    69,   107,   108,    75,    82,    83,   110,
       9,    10,    11,    12,    13,    84,    85,    86,    32,    33,
      34,   120,    71,    48,     0,    35,    36,    87,    38,    39,
       0,     0,     0,     0,     0,    40,    41,     0,     0,     0,
       0,     0,     0,    88,    42,     0,    82,    83,    43,     9,
      10,    11,    12,    13,    84,    85,    86,    32,    33,    34,
       0,     0,     0,     0,    35,    36,    87,    38,    39,     0,
       0,     0,     0,     0,    40,    41,     0,     0,     0,     0,
       0,     0,   106,    42,     0,    82,    83,    43,     9,    10,
      11,    12,    13,    84,    85,    86,    32,    33,    34,     0,
       0,     0,     0,    35,    36,    87,    38,    39,     0,     0,
       0,     0,     0,    40,    41,     0,     0,     0,     0,     0,
       0,   117,    42,     0,    82,    83,    43,     9,    10,    11,
      12,    13,    84,    85,    86,    32,    33,    34,     0,     0,
       0,     0,    35,    36,    87,    38,    39,     0,     0,     0,
       0,     0,    40,    41,     0,     0,     0,     0,     0,     0,
     118,    42,     0,    82,    83,    43,     9,    10,    11,    12,
      13,    84,    85,    86,    32,    33,    34,     0,     0,     0,
       0,    35,    36,    87,    38,    39,     0,     0,     0,     0,
       0,    40,    41,     0,     0,     0,     0,     0,     0,   122,
      42,    32,    33,    34,    43,     0,     0,     0,    35,    36,
      37,    38,    39,     0,     0,     0,     0,     0,    40,    41,
      57,    58,    59,    60,     0,     0,     0,    42,     0,     0,
       0,    43,    61,    62,    63,    64,    65,    66,    67,    57,
      58,    59,    60,     0,     0,     0,   105,     0,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    57,    58,
      59,    60,     0,     0,     0,   109,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    57,    58,    59,
      60,     0,   111,     0,     0,     0,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    57,    58,    59,    60,
       0,   112,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67
};

static const yysigned_char yycheck[] =
{
      24,    81,    28,    28,    26,     8,     6,     7,     8,     9,
      10,    42,    43,     0,    40,    40,    40,    41,    42,    43,
      23,    23,    38,    23,    23,    40,    40,    23,    52,    23,
      41,    40,    42,   113,   114,    28,    41,    38,    42,    39,
     120,    38,    40,    46,    68,     5,    41,     8,    51,    40,
      38,    43,    17,    18,    19,    20,    80,     6,     7,     8,
       9,    10,    86,    43,    29,    30,    31,    32,    33,    34,
      35,    43,    38,    46,    98,    99,    41,     3,     4,   103,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    38,    51,    26,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,     3,     4,    44,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    -1,     3,     4,    44,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    -1,     3,     4,    44,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,    -1,     3,     4,    44,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    14,    15,    16,    44,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,
      17,    18,    19,    20,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    44,    29,    30,    31,    32,    33,    34,    35,    17,
      18,    19,    20,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    17,    18,
      19,    20,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    17,    18,    19,
      20,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    17,    18,    19,    20,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    26,    46,    47,     0,    23,    48,    38,    49,     6,
       7,     8,     9,    10,    23,    39,    50,    53,    58,    52,
      23,    59,    60,    40,    28,    51,    42,    43,    53,    54,
      55,    56,    14,    15,    16,    21,    22,    23,    24,    25,
      31,    32,    40,    44,    65,    69,    40,    23,    60,    23,
      41,    42,    40,    65,    65,    65,    65,    17,    18,    19,
      20,    29,    30,    31,    32,    33,    34,    35,    68,    54,
      38,    56,    65,    66,    67,    41,    65,    41,    57,    41,
      42,    38,     3,     4,    11,    12,    13,    23,    39,    53,
      58,    61,    62,    63,    64,    65,    65,    57,    40,    40,
      43,    43,    65,    28,    43,    43,    39,    65,    65,    43,
      65,    41,    41,    38,    38,    57,    57,    39,    39,     5,
      38,    57,    39
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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

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
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
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
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
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

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
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

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 97 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    { 
				symbolTable->OpenScope();
				ReadWrite::ReadWriteAdd();
			;}
    break;

  case 3:
#line 100 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					symbolTable->AddSymbol((yyvsp[0].Tid) , 4  ,  6 );
				 ;}
    break;

  case 4:
#line 103 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
							(yyval.tClass) = new Class( (yyvsp[-4].Tid) , (yyvsp[-1].tSmall) , line , col);
							root = (yyval.tClass);
							//symbolTable->CloseScope();
						;}
    break;

  case 5:
#line 111 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.tSmall) = new Small(line , col );
		;}
    break;

  case 6:
#line 115 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tSmall) =  new Func_Small( (yyvsp[-1].tSmall) , (yyvsp[0].tfunc) , line , col);
				;}
    break;

  case 7:
#line 119 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
		(yyval.tSmall) =  new Var_Small( (yyvsp[-1].tSmall) , (yyvsp[0].tvar_decl) , line , col);
	   ;}
    break;

  case 8:
#line 124 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {		
							symbolTable->OpenScope();
							current_kind = 3;
							
							last_func = (yyvsp[-1].ttype_specifier)->type;
						  ;}
    break;

  case 9:
#line 130 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
											
											(yyval.tfunc) = new Func( (yyvsp[-8].ttype_specifier) , (yyvsp[-7].Tid) , (yyvsp[-4].tdecl_list) , (yyvsp[-1].tcomp) , line, col );
											symbolTable->CloseScope();
											current_kind = 2;
											symbolTable->AddFunc((yyvsp[-7].Tid) , 1 , (yyvsp[-4].tdecl_list) , (yyvsp[-8].ttype_specifier)->type , (yyval.tfunc) );
										;}
    break;

  case 10:
#line 137 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				symbolTable->OpenScope();
				current_kind = 3;
				symbolTable->LookupConstructor((yyvsp[0].Tid) );
			;}
    break;

  case 11:
#line 142 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
							(yyval.tfunc) = new Constructor( (yyvsp[-7].Tid) , (yyvsp[-4].tdecl_list) , (yyvsp[-1].tcomp) , line , col );
							symbolTable->CloseScope();
							last_func = 0;
						;}
    break;

  case 12:
#line 151 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.ttype_specifier) =  new Type( 1 , line , col );
						current_type= 1;
					
					;}
    break;

  case 13:
#line 157 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.ttype_specifier) =  new Type( 2 , line , col );
						current_type= 2;
					;}
    break;

  case 14:
#line 162 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.ttype_specifier) =  new Type( 3 , line , col );
						current_type= 3;
					;}
    break;

  case 15:
#line 167 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.ttype_specifier) =  new Type( 4 , line , col );
						current_type= 4;
					;}
    break;

  case 16:
#line 172 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.ttype_specifier) =  new Type( 5 , line , col );
						current_type= 5;
					;}
    break;

  case 17:
#line 180 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tdecl_list) = new Decl_List(line , col);
				;}
    break;

  case 18:
#line 184 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tdecl_list) = (yyvsp[0].tdecl_list);
				;}
    break;

  case 19:
#line 190 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyvsp[-2].tdecl_list)->AddParam((yyvsp[0].tParam_decl));
					(yyval.tdecl_list) = (yyvsp[-2].tdecl_list);
				;}
    break;

  case 20:
#line 195 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tdecl_list) = new Decl_List( (yyvsp[0].tParam_decl) ,line , col);

				;}
    break;

  case 21:
#line 202 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tParam_decl) = new Param_Decl((yyvsp[-1].ttype_specifier) , (yyvsp[0].Tid) , line , col);
					symbolTable->AddSymbol((yyvsp[0].Tid) , 3  , (yyvsp[-1].ttype_specifier)->type );
				;}
    break;

  case 22:
#line 209 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tcomp)= new Var_Comp((yyvsp[-1].tcomp) , (yyvsp[0].tvar_decl) , line , col);
			;}
    break;

  case 23:
#line 213 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tcomp)= new Stmt_Comp((yyvsp[-1].tcomp) , (yyvsp[0].tstmt) , line , col);
			;}
    break;

  case 24:
#line 217 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tcomp)= new Comp(line , col);
			;}
    break;

  case 25:
#line 224 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
								(yyval.tvar_decl)= new Var_Decl( (yyvsp[-2].ttype_specifier) , (yyvsp[-1].tvar_decl_list) , line , col);
				
							;}
    break;

  case 26:
#line 231 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
							(yyvsp[-2].tvar_decl_list)->AddVar((yyvsp[0].tvariable_id));
							(yyval.tvar_decl_list) = (yyvsp[-2].tvar_decl_list);
						;}
    break;

  case 27:
#line 236 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
							(yyval.tvar_decl_list) = new Var_Decl_List((yyvsp[0].tvariable_id) , line , col);
						;}
    break;

  case 28:
#line 242 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tvariable_id) = new Var_Id((yyvsp[0].Tid) , line , col);
					symbolTable->AddSymbol((yyvsp[0].Tid) , current_kind  , current_type );
				;}
    break;

  case 29:
#line 247 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tvariable_id) = new Var_Id_Exp( (yyvsp[-2].Tid) , (yyvsp[0].texpr) , line , col);
					symbolTable->AddSymbol((yyvsp[-2].Tid) , current_kind  , current_type );
				;}
    break;

  case 30:
#line 254 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tstmt) = (yyvsp[0].tstmt);
				;}
    break;

  case 31:
#line 258 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tstmt) = (yyvsp[0].tstmt);
				;}
    break;

  case 32:
#line 262 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tstmt) = new Break(line , col );
				;}
    break;

  case 33:
#line 266 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tstmt) = (yyvsp[-1].tstmt);
				;}
    break;

  case 34:
#line 270 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tstmt) = new Continue(line , col);
				;}
    break;

  case 35:
#line 274 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tstmt) = new RT_expr((yyvsp[-1].texpr),last_func, line , col ) ;
						
				;}
    break;

  case 36:
#line 279 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.tstmt) = new Stmt_expr( (yyvsp[-1].texpr) , line , col );
		 ;}
    break;

  case 37:
#line 285 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.tstmt) = new If((yyvsp[-4].texpr) , (yyvsp[-1].tcomp) , line , col);
					;}
    break;

  case 38:
#line 289 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.tstmt) = new If_Else((yyvsp[-8].texpr) , (yyvsp[-5].tcomp) , (yyvsp[-1].tcomp) , line , col);
					;}
    break;

  case 39:
#line 295 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				   (yyval.tstmt) = new While_Stmt( (yyvsp[-4].texpr) , (yyvsp[-1].tcomp) , line , col);
				;}
    break;

  case 40:
#line 301 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tstmt) = new assignStmt( (yyvsp[-2].Tid) , (yyvsp[0].texpr) , line , col);
				symbolTable->LookUp((yyvsp[-2].Tid) );
			;}
    break;

  case 41:
#line 308 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.texpr) = (yyvsp[0].tprimary);
		;}
    break;

  case 42:
#line 312 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.texpr) = new Expr_op_Expr( (yyvsp[-2].texpr) , (yyvsp[-1].toperator) , (yyvsp[0].texpr) , line , col);
		;}
    break;

  case 43:
#line 316 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.texpr) = new Ex_Expr( (yyvsp[0].texpr) , line , col);
		;}
    break;

  case 44:
#line 320 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.texpr) = new ParenthesesExpr((yyvsp[-1].texpr) , line , col);
		;}
    break;

  case 45:
#line 324 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.texpr) = new MinusExpr((yyvsp[0].texpr) , line , col);
		;}
    break;

  case 46:
#line 328 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.texpr) = new PlusExpr((yyvsp[0].texpr) , line , col);
		;}
    break;

  case 47:
#line 332 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
			(yyval.texpr) = new Id_Expr_list( (yyvsp[-3].Tid) , (yyvsp[-1].texprList) , line , col);
			//symbolTable->LookupFunction($1 );
		;}
    break;

  case 48:
#line 339 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.texprList) = new Expr_List(line , col );
				;}
    break;

  case 49:
#line 343 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
						(yyval.texprList) = (yyvsp[0].texprList);
					;}
    break;

  case 50:
#line 349 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.texprList) = new Expr_List((yyvsp[0].texpr), line , col);
				;}
    break;

  case 51:
#line 353 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				  (yyvsp[-2].texprList)->addExpression((yyvsp[0].texpr));
				  (yyval.texprList) = (yyvsp[-2].texprList);
				;}
    break;

  case 52:
#line 360 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 1;
				;}
    break;

  case 53:
#line 364 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 2;
				;}
    break;

  case 54:
#line 368 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 3;
				;}
    break;

  case 55:
#line 372 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 4;
				;}
    break;

  case 56:
#line 376 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 5;
				;}
    break;

  case 57:
#line 380 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 6;
				;}
    break;

  case 58:
#line 384 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 7;
				;}
    break;

  case 59:
#line 388 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 8;
				;}
    break;

  case 60:
#line 392 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 9;
				;}
    break;

  case 61:
#line 396 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 10;
				;}
    break;

  case 62:
#line 400 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
					(yyval.toperator) = 11;
				;}
    break;

  case 63:
#line 406 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary)= (yyvsp[0].tINTNUM);
				;}
    break;

  case 64:
#line 410 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary)= (yyvsp[0].tFLOATNUM);
				;}
    break;

  case 65:
#line 414 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary)= (yyvsp[0].tCHARCONST);
				;}
    break;

  case 66:
#line 418 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary)= new String_value(strdup(yytext),line,col);
				;}
    break;

  case 67:
#line 422 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary) = new Primary_ID((yyvsp[0].Tid) , line , col);
				symbolTable->LookUp((yyvsp[0].Tid));
				;}
    break;

  case 68:
#line 427 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary) = new True_value(line,col);
				;}
    break;

  case 69:
#line 431 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary) = new False_value(line,col);
				;}
    break;

  case 70:
#line 435 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"
    {
				(yyval.tprimary)= new Null_value(line,col);
				;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 1866 "parser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
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
	  int yychecklim = YYLAST - yyn;
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
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
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
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
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
	  yydestruct ("Error: discarding", yytoken, &yylval);
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
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 439 "D:\\3d max\\final submission\\ConsoleApplication3\\ConsoleApplication3\\parser.y"


int yyerror(const char *s1){
cout << "Parsing Error !!! in line= " <<line <<"and col= " <<col <<endl;
return 1;
}


