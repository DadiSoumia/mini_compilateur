%{
#include <stdio.h>
#include <stdlib.h>

 extern int nb_ligne;
 extern int yylex();
 void yyerror(const char *msg);

extern int yylex();
void yyerror(const char *s);
%}

%token begin endProject setup run  define const_kw
%token cst integer  float_kw float_signe integer_signe 
%token  if_kw then else_kw endIf
%token  loop while_kw endloop for_kw in to endfor out  affectation
%token  add sus mult Div AND OR NON
%token  sup_egal inf_egal egal diff sup inf 
%token pointverg deuxpoint barre virgule  crochetO crochetF parO parF acolO acolF  egg
%token chaine  idf
%token erreur 


%left   egal 
%left add sus mult Div
%right affectation

%%
S: begin idf pointverg  setup deuxpoint DECS run deuxpoint acolO INSTRUCTION acolF endProject pointverg
    ;

DECS : DEC DECS
    |
    ;

DEC : define  LISTIDF deuxpoint TYPE  pointverg DEC 
    | define LISTIDF deuxpoint TYPE  egg CONST pointverg DEC
    | DECTABLE
    | DECCONST
	;

DECTABLE : define idf deuxpoint crochetO TYPE pointverg integer crochetF pointverg DECTABLE
    ;

DECCONST : const_kw idf deuxpoint TYPE egg CONST pointverg DECCONST
    ; 

CONST : integer 
    | float_kw
    | float_signe 
    | integer_signe 
    ;

TYPE : integer 
    | float_kw
    ;

LISTIDF :  idf barre LISTIDF
    | idf
    ;

INSTRUCTION  : BOUCLE
    | CONDIF
    | LECTURE_ECRITURE   
    ;

CONDIF : if_kw parO CONDITION parF then deuxpoint acolO INSTRUCTION acolF else_kw acolO INSTRUCTION acolF endIf pointverg
    | if_kw parO CONDITION parF then deuxpoint acolO INSTRUCTION acolF endIf pointverg
    ;
LECTURE_ECRITURE : out parO chaine parF pointverg
   
    ;

    ;
BOUCLE : loop while_kw parO CONDITION parF acolO INSTRUCTION acolF endloop 
    ;
CONDITION : EXPR LOGIQUE EXPR
    | EXPR
    ;
EXPR : EXPR add EXPR
    | EXPR sus EXPR     
    | EXPR mult EXPR
    | EXPR Div EXPR
    | EXPR sup_egal EXPR
    | EXPR inf_egal EXPR
    | EXPR egal EXPR
    | EXPR diff EXPR
    | EXPR sup EXPR
    | EXPR inf EXPR
    | parO EXPR parF
    | idf
    | cst
    | chaine
     ;
LOGIQUE : AND
        | OR
        | NON
        ;



%%


void yyerror(const char *msg) {
    fprintf(stderr, "Erreur syntaxique a la ligne %d : %s\n", nb_ligne, msg);
}

int main() {
    yyparse();
    printf("Analyse syntaxique correct \n");
    return 0;
}