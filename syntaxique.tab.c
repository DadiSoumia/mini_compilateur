
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "syntaxique.y"

#include <stdio.h>
#include <stdlib.h>
#include "ts.h"
#include "quad.h"

int temp_var_count = 0; // Compteur pour les variables temporaires des quadruplets

extern int nb_ligne;
extern int nb_colonne;
extern int yylex();
extern char* yytext;
void yyerror(const char *msg);
void yyerror(const char *s);

int nb_erreur_sem = 0; // Compteur d'erreurs semantiques



/* Line 189 of yacc.c  */
#line 93 "syntaxique.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     begin = 258,
     endProject = 259,
     setup = 260,
     run = 261,
     define = 262,
     const_kw = 263,
     integer = 264,
     float_kw = 265,
     if_kw = 266,
     then = 267,
     else_kw = 268,
     endIf = 269,
     loop = 270,
     while_kw = 271,
     endloop = 272,
     for_kw = 273,
     in_kw = 274,
     to = 275,
     endfor = 276,
     out = 277,
     in_put = 278,
     affectation = 279,
     add = 280,
     sus = 281,
     mult = 282,
     Div = 283,
     AND = 284,
     OR = 285,
     NON = 286,
     sup_egal = 287,
     inf_egal = 288,
     egal = 289,
     diff = 290,
     sup = 291,
     inf = 292,
     pointverg = 293,
     deuxpoint = 294,
     barre = 295,
     virgule = 296,
     crochetO = 297,
     crochetF = 298,
     parO = 299,
     parF = 300,
     acolO = 301,
     acolF = 302,
     egg = 303,
     erreur = 304,
     idf = 305,
     cst = 306,
     float_signe = 307,
     integer_signe = 308,
     chaine = 309
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 23 "syntaxique.y"

    char* str;   // Pour transporter des noms d'identifiants ou des types
    struct {
        char type[20]; // Pour stocker le type d'une expression (int/float)
        char val[50];  // Pour stocker la valeur textuelle d'une expression
    } expr;



/* Line 214 of yacc.c  */
#line 193 "syntaxique.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 205 "syntaxique.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNRULES -- Number of states.  */
#define YYNSTATES  167

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    17,    20,    21,    23,    25,    27,    33,
      41,    47,    55,    65,    73,    75,    77,    79,    81,    83,
      87,    91,    94,    95,    97,    99,   101,   103,   108,   116,
     124,   140,   152,   160,   166,   172,   183,   195,   197,   201,
     205,   209,   213,   217,   221,   225,   229,   233,   237,   241,
     243,   245,   247,   249,   253,   257,   260
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,     3,    50,    38,     5,    39,    57,     6,
      39,    46,    65,    47,     4,    38,    -1,    58,    57,    -1,
      -1,    59,    -1,    60,    -1,    61,    -1,     7,    50,    39,
      63,    38,    -1,     7,    50,    39,    63,    48,    62,    38,
      -1,     7,    64,    39,    63,    38,    -1,     7,    64,    39,
      63,    48,    62,    38,    -1,     7,    50,    39,    42,    63,
      38,    62,    43,    38,    -1,     8,    50,    39,    63,    48,
      62,    38,    -1,    51,    -1,    52,    -1,    53,    -1,     9,
      -1,    10,    -1,    50,    40,    50,    -1,    50,    40,    64,
      -1,    66,    65,    -1,    -1,    67,    -1,    70,    -1,    68,
      -1,    69,    -1,    50,    24,    72,    38,    -1,    50,    42,
      51,    43,    24,    72,    38,    -1,    50,    42,    50,    43,
      24,    72,    38,    -1,    11,    44,    71,    45,    12,    39,
      46,    65,    47,    13,    46,    65,    47,    14,    38,    -1,
      11,    44,    71,    45,    12,    39,    46,    65,    47,    14,
      38,    -1,    22,    44,    54,    41,    72,    45,    38,    -1,
      22,    44,    54,    45,    38,    -1,    23,    44,    50,    45,
      38,    -1,    15,    16,    44,    71,    45,    46,    65,    47,
      17,    38,    -1,    18,    50,    19,    62,    20,    62,    46,
      65,    47,    21,    38,    -1,    72,    -1,    72,    25,    72,
      -1,    72,    26,    72,    -1,    72,    27,    72,    -1,    72,
      28,    72,    -1,    72,    32,    72,    -1,    72,    33,    72,
      -1,    72,    34,    72,    -1,    72,    35,    72,    -1,    72,
      36,    72,    -1,    72,    37,    72,    -1,    44,    72,    45,
      -1,    50,    -1,    62,    -1,    54,    -1,    73,    -1,    72,
      29,    72,    -1,    72,    30,    72,    -1,    31,    72,    -1,
      50,    42,    72,    43,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    63,    64,    67,    68,    69,    73,    83,
      93,   110,   130,   143,   155,   156,   157,   162,   163,   167,
     172,   179,   180,   184,   185,   186,   187,   191,   217,   245,
     279,   280,   287,   288,   289,   299,   300,   311,   314,   321,
     328,   335,   347,   348,   349,   350,   351,   352,   353,   354,
     369,   375,   377,   378,   379,   380,   383
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "begin", "endProject", "setup", "run",
  "define", "const_kw", "integer", "float_kw", "if_kw", "then", "else_kw",
  "endIf", "loop", "while_kw", "endloop", "for_kw", "in_kw", "to",
  "endfor", "out", "in_put", "affectation", "add", "sus", "mult", "Div",
  "AND", "OR", "NON", "sup_egal", "inf_egal", "egal", "diff", "sup", "inf",
  "pointverg", "deuxpoint", "barre", "virgule", "crochetO", "crochetF",
  "parO", "parF", "acolO", "acolF", "egg", "erreur", "idf", "cst",
  "float_signe", "integer_signe", "chaine", "$accept", "S", "DECS", "DEC",
  "VAR_DEC", "DECTABLE", "DECCONST", "CONST", "TYPE", "LISTIDF",
  "INSTRUCTIONS", "INSTRUCTION", "AFFECTATION", "CONDIF",
  "LECTURE_ECRITURE", "BOUCLE", "CONDITION", "EXPR", "TAB", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    58,    59,    59,
      59,    59,    60,    61,    62,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    66,    66,    67,    67,    67,
      68,    68,    69,    69,    69,    70,    70,    71,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    13,     2,     0,     1,     1,     1,     5,     7,
       5,     7,     9,     7,     1,     1,     1,     1,     1,     3,
       3,     2,     0,     1,     1,     1,     1,     4,     7,     7,
      15,    11,     7,     5,     5,    10,    11,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     3,     3,     2,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     4,     0,     0,
       0,     4,     5,     6,     7,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,    17,    18,     0,     0,    19,
      20,     0,     0,    22,     0,     8,     0,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,    25,
      26,    24,     0,    14,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     9,
      11,    13,     0,     0,    49,    51,    50,     0,    37,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,     0,     0,     2,    12,    48,     0,     0,    38,    39,
      40,    41,    53,    54,    42,    43,    44,    45,    46,    47,
       0,     0,     0,    33,    34,     0,     0,    56,     0,    22,
       0,     0,     0,     0,    22,     0,    22,    32,    29,    28,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
      22,    31,    36,     0,     0,     0,    30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    10,    11,    12,    13,    14,    76,    28,    16,
      46,    47,    48,    49,    50,    51,    77,    78,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -63
static const yytype_int16 yypact[] =
{
       4,   -41,    14,    -8,   -63,    39,    25,    86,    16,    22,
      92,    86,   -63,   -63,   -63,    31,    42,    67,   100,   -63,
      12,   103,   169,   169,    68,   -63,   -63,   169,   -32,    85,
     -63,   -25,   119,    -3,   142,   -63,    64,   -63,    64,    64,
     150,   177,   145,   152,   153,    19,   151,    -3,   -63,   -63,
     -63,   -63,    64,   -63,   -63,   -63,   161,   163,   164,   -26,
     156,   184,   154,   155,   -26,   137,   200,   -63,   166,   -63,
     -63,   -63,   -26,   -26,   165,   -63,   -63,   167,   136,   -63,
     -26,    64,    24,   168,    94,   171,   172,   173,   179,   149,
      23,   -26,   194,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   174,   190,   -26,   180,   182,
     -63,   192,   197,   -63,   -63,   -63,    75,   183,   162,   162,
     -63,   -63,   149,   149,    63,    63,    63,    63,    63,    63,
     181,    64,    50,   -63,   -63,   -26,   -26,   -63,   185,    -3,
     186,   187,   108,   122,    -3,   176,    -3,   -63,   -63,   -63,
     188,   207,   189,   178,   191,   205,   193,   195,   -63,   196,
      -3,   -63,   -63,   198,   214,   199,   -63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -63,   -63,   219,   -63,   -63,   -63,   -63,   -35,    40,   217,
     -47,   -63,   -63,   -63,   -63,   -63,   160,   -62,   -63
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      67,    56,    84,    57,    58,    72,    35,     1,    40,     3,
      89,    90,    41,    37,     4,    42,    36,    68,    73,    43,
      44,    25,    26,    38,    74,    53,    54,    55,    75,   116,
       5,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    64,     6,   132,   106,    45,    93,    94,
      95,    96,    97,    98,    27,    99,   100,   101,   102,   103,
     104,    65,    31,    32,     7,   107,    15,    34,   115,   108,
      20,    21,    17,   142,   143,    93,    94,    95,    96,    97,
      98,    22,    99,   100,   101,   102,   103,   104,    93,    94,
      95,    96,   145,     8,     9,   141,   140,   150,    18,   152,
      93,    94,    95,    96,    97,    98,    23,    99,   100,   101,
     102,   103,   104,   163,    33,    53,    54,    55,   137,    93,
      94,    95,    96,    97,    98,    21,    99,   100,   101,   102,
     103,   104,   110,    93,    94,    95,    96,    97,    98,    24,
      99,   100,   101,   102,   103,   104,   148,    93,    94,    95,
      96,    97,    98,    29,    99,   100,   101,   102,   103,   104,
     149,    93,    94,    95,    96,    97,    98,    39,    99,   100,
     101,   102,   103,   104,    93,    94,    95,    96,    25,    26,
      52,    99,   100,   101,   102,   103,   104,    85,    86,    95,
      96,   156,   157,    60,    59,    61,    62,    63,    66,    69,
      80,    70,    71,    81,    87,    83,   117,    91,    82,    88,
     131,   113,    92,   109,   111,   112,   135,   114,   133,   130,
     134,   136,   138,   151,   154,   147,   159,   139,   165,   158,
      19,   144,   146,   161,   162,   153,   155,   166,    30,   160,
     105,     0,     0,     0,     0,   164
};

static const yytype_int16 yycheck[] =
{
      47,    36,    64,    38,    39,    31,    38,     3,    11,    50,
      72,    73,    15,    38,     0,    18,    48,    52,    44,    22,
      23,     9,    10,    48,    50,    51,    52,    53,    54,    91,
      38,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,    24,     5,   107,    81,    50,    25,    26,
      27,    28,    29,    30,    42,    32,    33,    34,    35,    36,
      37,    42,    22,    23,    39,    41,    50,    27,    45,    45,
      39,    40,    50,   135,   136,    25,    26,    27,    28,    29,
      30,    39,    32,    33,    34,    35,    36,    37,    25,    26,
      27,    28,   139,     7,     8,    45,   131,   144,     6,   146,
      25,    26,    27,    28,    29,    30,    39,    32,    33,    34,
      35,    36,    37,   160,    46,    51,    52,    53,    43,    25,
      26,    27,    28,    29,    30,    40,    32,    33,    34,    35,
      36,    37,    38,    25,    26,    27,    28,    29,    30,    39,
      32,    33,    34,    35,    36,    37,    38,    25,    26,    27,
      28,    29,    30,    50,    32,    33,    34,    35,    36,    37,
      38,    25,    26,    27,    28,    29,    30,    48,    32,    33,
      34,    35,    36,    37,    25,    26,    27,    28,     9,    10,
      38,    32,    33,    34,    35,    36,    37,    50,    51,    27,
      28,    13,    14,    16,    44,    50,    44,    44,    47,    38,
      44,    38,    38,    19,     4,    50,    12,    42,    54,    43,
      20,    38,    45,    45,    43,    43,    24,    38,    38,    45,
      38,    24,    39,    47,    17,    38,    21,    46,    14,    38,
      11,    46,    46,    38,    38,    47,    47,    38,    21,    46,
      80,    -1,    -1,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    56,    50,     0,    38,     5,    39,     7,     8,
      57,    58,    59,    60,    61,    50,    64,    50,     6,    57,
      39,    40,    39,    39,    39,     9,    10,    42,    63,    50,
      64,    63,    63,    46,    63,    38,    48,    38,    48,    48,
      11,    15,    18,    22,    23,    50,    65,    66,    67,    68,
      69,    70,    38,    51,    52,    53,    62,    62,    62,    44,
      16,    50,    44,    44,    24,    42,    47,    65,    62,    38,
      38,    38,    31,    44,    50,    54,    62,    71,    72,    73,
      44,    19,    54,    50,    72,    50,    51,     4,    43,    72,
      72,    42,    45,    25,    26,    27,    28,    29,    30,    32,
      33,    34,    35,    36,    37,    71,    62,    41,    45,    45,
      38,    43,    43,    38,    38,    45,    72,    12,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      45,    20,    72,    38,    38,    24,    24,    43,    39,    46,
      62,    45,    72,    72,    46,    65,    46,    38,    38,    38,
      65,    47,    65,    47,    17,    47,    13,    14,    38,    21,
      46,    38,    38,    65,    47,    14,    38
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 8:

/* Line 1455 of yacc.c  */
#line 74 "syntaxique.y"
    {
            if (checkdeclaration((yyvsp[(2) - (5)].str))) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", (yyvsp[(2) - (5)].str), nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].str), "", 0);
            }
        ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 84 "syntaxique.y"
    {
            if (checkdeclaration((yyvsp[(2) - (7)].str))) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", (yyvsp[(2) - (7)].str), nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, (yyvsp[(2) - (7)].str), (yyvsp[(4) - (7)].str), (yyvsp[(6) - (7)].str), 0); // 0 is variable
            }
        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 94 "syntaxique.y"
    {
            // Pour les listes (a|b|c), on utilise la chaîne déjà allouée
            char *list = (yyvsp[(2) - (5)].str);
            char *token = strtok(list, "|");  // On sépare par le caractère '|'

            while(token != NULL) {
                if (checkdeclaration(token)) {
                    printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", token, nb_ligne, nb_colonne);
                 
                } else {
                    InsererSymbol(table, token, (yyvsp[(4) - (5)].str), "", 0);
                }
                token = strtok(NULL, "|");
            }
            free(list);
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 111 "syntaxique.y"
    {
            char *list = (yyvsp[(2) - (7)].str);
            char *token = strtok(list, "|");

            while(token != NULL) {
                if (checkdeclaration(token)) {
                    printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", token, nb_ligne, nb_colonne);
                    
                    
                } else {
                    InsererSymbol(table, token, (yyvsp[(4) - (7)].str), (yyvsp[(6) - (7)].str), 0); // 0 is variable
                }
                token = strtok(NULL, "|"); // Passe à l'identifiant suivant
            }
            free(list);
        ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 131 "syntaxique.y"
    {
            if (checkdeclaration((yyvsp[(2) - (9)].str))) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", (yyvsp[(2) - (9)].str), nb_ligne, nb_colonne); 
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, (yyvsp[(2) - (9)].str), (yyvsp[(5) - (9)].str), "", 2);
            }
        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 144 "syntaxique.y"
    {
            if (checkdeclaration((yyvsp[(2) - (7)].str))) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", (yyvsp[(2) - (7)].str), nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, (yyvsp[(2) - (7)].str), (yyvsp[(4) - (7)].str), (yyvsp[(6) - (7)].str), 1);
            }
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 155 "syntaxique.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 156 "syntaxique.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 157 "syntaxique.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 162 "syntaxique.y"
    { (yyval.str) = "int"; ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 163 "syntaxique.y"
    { (yyval.str) = "float"; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 168 "syntaxique.y"
    {
            (yyval.str) = malloc(strlen((yyvsp[(1) - (3)].str)) + strlen((yyvsp[(3) - (3)].str)) + 2);
            sprintf((yyval.str), "%s|%s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 173 "syntaxique.y"
    {
            (yyval.str) = malloc(strlen((yyvsp[(1) - (3)].str)) + strlen((yyvsp[(3) - (3)].str)) + 2);
            sprintf((yyval.str), "%s|%s", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
        ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 192 "syntaxique.y"
    {
            if (!checkdeclaration((yyvsp[(1) - (4)].str))) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", (yyvsp[(1) - (4)].str), nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InfoSymboles *ent = Rechercher(table, (yyvsp[(1) - (4)].str));
                int has_error = 0;
                if (ent->Etat == 1) {
                    printf("Erreur SYMENTIQUE: Modification d'une constante '%s', a la ligne '%d' , et la colonne '%d' : \n", (yyvsp[(1) - (4)].str), nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (strcmp(ent->Type, "int") == 0 && strcmp((yyvsp[(3) - (4)].expr).type, "float") == 0) {
                    printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", (yyvsp[(1) - (4)].str), nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (!has_error) {
                    MettreAJourSymbol(table, (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].expr).val, NULL, ent->Etat);
                    quadr("=", (yyvsp[(3) - (4)].expr).val, "", (yyvsp[(1) - (4)].str));
                }
            }
        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 218 "syntaxique.y"
    {
            if (!checkdeclaration((yyvsp[(1) - (7)].str))) {
                printf("Erreur SYMENTIQUE: Non declaration du tableau '%s', a la ligne '%d', et la colonne '%d' : \n", (yyvsp[(1) - (7)].str), nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InfoSymboles *ent = Rechercher(table, (yyvsp[(1) - (7)].str));
                int has_error = 0;
                if (ent->Etat == 1) {
                    printf("Erreur SYMENTIQUE: Modification d'une constante '%s', a la ligne '%d' , et la colonne '%d' : \n", (yyvsp[(1) - (7)].str), nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (strcmp(ent->Type, "int") == 0 && strcmp((yyvsp[(6) - (7)].expr).type, "float") == 0) {
                    printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un tableau d'int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", (yyvsp[(1) - (7)].str), nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (!has_error) {
                    MettreAJourSymbol(table, (yyvsp[(1) - (7)].str), (yyvsp[(6) - (7)].expr).val, NULL, ent->Etat);
                    char tmp_arr[50];
                    sprintf(tmp_arr, "%s[%s]", (yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].str));
                    quadr("=", (yyvsp[(6) - (7)].expr).val, "", tmp_arr);
                }
            }
        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 246 "syntaxique.y"
    {
            if (!checkdeclaration((yyvsp[(1) - (7)].str))) {
                printf("Erreur Semantique: %s tableau non declare\n", (yyvsp[(1) - (7)].str));
                nb_erreur_sem++;
            } else if (!checkdeclaration((yyvsp[(3) - (7)].str))) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", (yyvsp[(3) - (7)].str), nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InfoSymboles *ent = Rechercher(table, (yyvsp[(1) - (7)].str));
                int has_error = 0;
                if (ent->Etat == 1) {
                    printf("Erreur SYMENTIQUE: Modification d'une constante '%s', a la ligne '%d' , et la colonne '%d' : \n", (yyvsp[(1) - (7)].str), nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (strcmp(ent->Type, "int") == 0 && strcmp((yyvsp[(6) - (7)].expr).type, "float") == 0) {
                    printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un tableau d'int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", (yyvsp[(1) - (7)].str), nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (!has_error) {
                    MettreAJourSymbol(table, (yyvsp[(1) - (7)].str), (yyvsp[(6) - (7)].expr).val, NULL, ent->Etat);
                    char tmp_arr[50];
                    sprintf(tmp_arr, "%s[%s]", (yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].str));
                    quadr("=", (yyvsp[(6) - (7)].expr).val, "", tmp_arr);
                }
            }
        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 281 "syntaxique.y"
    {
    // bool type 
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 290 "syntaxique.y"
    {
        if (!checkdeclaration((yyvsp[(3) - (5)].str))) {
            printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", (yyvsp[(3) - (5)].str), nb_ligne, nb_colonne);
            nb_erreur_sem++;
        }
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 301 "syntaxique.y"
    {
            if (!checkdeclaration((yyvsp[(2) - (11)].str))) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", (yyvsp[(2) - (11)].str), nb_ligne, nb_colonne);
                nb_erreur_sem++;
            }
        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 315 "syntaxique.y"
    {
        if (strcmp((yyvsp[(1) - (3)].expr).type, "float") == 0 || strcmp((yyvsp[(3) - (3)].expr).type, "float") == 0) strcpy((yyval.expr).type, "float");    
        else strcpy((yyval.expr).type, "int");
        sprintf((yyval.expr).val, "T%d", temp_var_count++);
        quadr("+", (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val);
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 322 "syntaxique.y"
    {
        if (strcmp((yyvsp[(1) - (3)].expr).type, "float") == 0 || strcmp((yyvsp[(3) - (3)].expr).type, "float") == 0) strcpy((yyval.expr).type, "float");
        else strcpy((yyval.expr).type, "int");
        sprintf((yyval.expr).val, "T%d", temp_var_count++);
        quadr("-", (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val);
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 329 "syntaxique.y"
    {
        if (strcmp((yyvsp[(1) - (3)].expr).type, "float") == 0 || strcmp((yyvsp[(3) - (3)].expr).type, "float") == 0) strcpy((yyval.expr).type, "float");
        else strcpy((yyval.expr).type, "int");
        sprintf((yyval.expr).val, "T%d", temp_var_count++);
        quadr("*", (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val);
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 336 "syntaxique.y"
    {
        if (strcmp((yyvsp[(3) - (3)].expr).val, "0") == 0 || strcmp((yyvsp[(3) - (3)].expr).val, "0.0") == 0 || strcmp((yyvsp[(3) - (3)].expr).val, "(+0)") == 0) {
            printf("Erreur SYMENTIQUE: Division par zero detectee a la ligne '%d' et la colonne '%d' : \n", nb_ligne, nb_colonne);
            nb_erreur_sem++;
        }
        if (strcmp((yyvsp[(1) - (3)].expr).type, "float") == 0 || strcmp((yyvsp[(3) - (3)].expr).type, "float") == 0) strcpy((yyval.expr).type, "float");
        else strcpy((yyval.expr).type, "int");
        sprintf((yyval.expr).val, "T%d", temp_var_count++);
        quadr("/", (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val);
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 347 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadC(2, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 348 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadC(4, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 349 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadC(5, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 350 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadC(6, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 351 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadC(1, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 352 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadC(3, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 353 "syntaxique.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 355 "syntaxique.y"
    {
        if (!checkdeclaration((yyvsp[(1) - (1)].str))) {
            printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", (yyvsp[(1) - (1)].str), nb_ligne, nb_colonne);
           
        }
        InfoSymboles *ent = Rechercher(table, (yyvsp[(1) - (1)].str));
        if(ent) {
            strcpy((yyval.expr).type, ent->Type);
            strcpy((yyval.expr).val, (yyvsp[(1) - (1)].str));
        } else {
            strcpy((yyval.expr).type, "");
            strcpy((yyval.expr).val, "");
        }
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 370 "syntaxique.y"
    {
        if (strchr((yyvsp[(1) - (1)].str), '.') != NULL) strcpy((yyval.expr).type, "float");
        else strcpy((yyval.expr).type, "int");
        strcpy((yyval.expr).val, (yyvsp[(1) - (1)].str));
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 375 "syntaxique.y"
    { strcpy((yyval.expr).type, "chaine"); strcpy((yyval.expr).val, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 377 "syntaxique.y"
    { strcpy((yyval.expr).type, (yyvsp[(1) - (1)].expr).type); strcpy((yyval.expr).val, (yyvsp[(1) - (1)].expr).val); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 378 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadL(1, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 379 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadL(2, (yyvsp[(1) - (3)].expr).val, (yyvsp[(3) - (3)].expr).val, (yyval.expr).val); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 380 "syntaxique.y"
    { strcpy((yyval.expr).type, "int"); sprintf((yyval.expr).val, "T%d", temp_var_count++); quadL(3, (yyvsp[(2) - (2)].expr).val, "", (yyval.expr).val); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 384 "syntaxique.y"
    {
        if (!checkdeclaration((yyvsp[(1) - (4)].str))) {
            printf("Erreur Semantique : tableau %s est non declare\n", (yyvsp[(1) - (4)].str));
           
        }
        InfoSymboles *ent = Rechercher(table, (yyvsp[(1) - (4)].str));
        if(ent) {
            strcpy((yyval.expr).type, ent->Type);
            sprintf((yyval.expr).val, "%s[%s]", (yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].expr).val);
        } else {
            strcpy((yyval.expr).type, "");
            strcpy((yyval.expr).val, "");
        }
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2014 "syntaxique.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 403 "syntaxique.y"


void yyerror(const char *msg) {
    fprintf(stderr, "Erreur Syntaxique, ligne %d, colonne %d, entite : %s\n", nb_ligne, nb_colonne, yytext, msg);
}

int main() {
    table = createHashTable(50);
    printf("Lancement Analyse Syntaxique\n");
    if (yyparse() == 0) {
        printf("Analyse syntaxique correcte\n");
        if (nb_erreur_sem == 0) {
            printf("Analyse semantique correcte\n");
        } else {
            printf("Analyse semantique terminee avec %d erreurs\n", nb_erreur_sem);
        }
        AfficherTableHG(table);
        afficher_qdr();
    }


    return 0;
}

