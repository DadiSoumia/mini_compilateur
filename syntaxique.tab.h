
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 23 "syntaxique.y"

    char* str;   // Pour transporter des noms d'identifiants ou des types
    struct {
        char type[20]; // Pour stocker le type d'une expression (int/float)
        char val[50];  // Pour stocker la valeur textuelle d'une expression
    } expr;



/* Line 1676 of yacc.c  */
#line 116 "syntaxique.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


