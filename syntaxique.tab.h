
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
     cst = 264,
     integer = 265,
     float_kw = 266,
     float_signe = 267,
     integer_signe = 268,
     if_kw = 269,
     then = 270,
     else_kw = 271,
     endIf = 272,
     loop = 273,
     while_kw = 274,
     endloop = 275,
     for_kw = 276,
     in_kw = 277,
     to = 278,
     endfor = 279,
     out = 280,
     affectation = 281,
     add = 282,
     sus = 283,
     mult = 284,
     Div = 285,
     AND = 286,
     OR = 287,
     NON = 288,
     sup_egal = 289,
     inf_egal = 290,
     egal = 291,
     diff = 292,
     sup = 293,
     inf = 294,
     pointverg = 295,
     deuxpoint = 296,
     barre = 297,
     virgule = 298,
     crochetO = 299,
     crochetF = 300,
     parO = 301,
     parF = 302,
     acolO = 303,
     acolF = 304,
     egg = 305,
     chaine = 306,
     idf = 307,
     erreur = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


