%{
#include <stdio.h>
#include <stdlib.h>

extern int nb_ligne;
extern int nb_colonne;
extern int yylex();
extern char* yytext;
void yyerror(const char *msg);
void yyerror(const char *s);

%}

%token begin endProject setup run define const_kw
%token cst integer float_kw float_signe integer_signe 
%token if_kw then else_kw endIf
%token loop while_kw endloop for_kw in_kw to endfor out affectation
%token add sus mult Div AND OR NON
%token sup_egal inf_egal egal diff sup inf 
%token pointverg deuxpoint barre virgule crochetO crochetF parO parF acolO acolF egg
%token chaine idf
%token erreur 

// priorités 
%right affectation
%left AND OR NON

%left inf inf_egal sup sup_egal egal diff
%left add sus
%left mult Div

%%
//Structure Globale : BeginProject Nom_Prog ; Setup : Declarations run : { Instructions } EndProject ; 
S: begin idf pointverg setup deuxpoint DECS run deuxpoint acolO INSTRUCTIONS acolF endProject pointverg
    ;

// Déclarations 
DECS : DEC DECS
    |
    ;

DEC : VAR_DEC
    | DECTABLE
    | DECCONST
	;

// Déclaration d'une Variable simple ou en Liste sans conflit
VAR_DEC : define idf deuxpoint TYPE pointverg
        | define idf deuxpoint TYPE egg CONST pointverg
        | define LISTIDF deuxpoint TYPE pointverg
        | define LISTIDF deuxpoint TYPE egg CONST pointverg
        ;
       
// Déclaration d'un Tableau 
DECTABLE : define idf deuxpoint crochetO TYPE pointverg CONST crochetF pointverg
    ;

// Déclaration d'une Constante 
DECCONST : const_kw idf deuxpoint TYPE egg CONST pointverg
    ; 

CONST : cst
    | float_signe 
    | integer_signe 
    ;


TYPE : integer 
    | float_kw
    ;

// Déclaration multiple de variables 
LISTIDF : idf barre idf
    | idf barre LISTIDF
    ;

INSTRUCTIONS : INSTRUCTION INSTRUCTIONS
    | /* vide */
    ;


INSTRUCTION : AFFECTATION
    | BOUCLE
    | CONDIF
    | LECTURE_ECRITURE   
    ;


AFFECTATION : idf affectation EXPR pointverg
    |  idf crochetO cst crochetF  affectation EXPR pointverg
    |  idf crochetO idf crochetF  affectation EXPR pointverg
    ;


CONDIF : if_kw parO CONDITION parF then deuxpoint acolO INSTRUCTIONS acolF else_kw acolO INSTRUCTIONS acolF endIf pointverg
    | if_kw parO CONDITION parF then deuxpoint acolO INSTRUCTIONS acolF endIf pointverg
    ;


LECTURE_ECRITURE : out parO chaine virgule EXPR parF pointverg
    | out parO chaine parF pointverg
    | in_kw parO idf parF pointverg
    ;

BOUCLE : loop while_kw parO CONDITION parF acolO INSTRUCTIONS acolF endloop pointverg
    | for_kw idf in_kw CONST to CONST acolO INSTRUCTIONS acolF endfor pointverg
    ;

CONDITION : 
 EXPR
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
    | CONST
    | chaine
    | TAB
    | EXPR AND EXPR
    | EXPR OR EXPR
    | NON EXPR
    ;

TAB : idf crochetO EXPR crochetF





%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erreur Syntaxique, ligne %d, colonne %d, entite : %s\n", nb_ligne, nb_colonne, yytext, msg);
}

int main() {
    printf("Lancement Analyse Syntaxique\n");
    if (yyparse() == 0) {
        printf("Analyse syntaxique correcte\n");
    }
    return 0;
}
