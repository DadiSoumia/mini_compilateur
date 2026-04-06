%{
#include <stdio.h>
#include <stdlib.h>
#include <ts.h>

extern int nb_ligne;
extern int nb_colonne;
extern int yylex();
extern char* yytext;
void yyerror(const char *msg);
void yyerror(const char *s);

%}

// types

%union {
    char* str;
    struct {
        char type[20];
        char val[50];
    } expr;
}

%type <str> TYPE CONST LISTIDF TAB
%type <expr> EXPR
/*
    char* typename;
    char* name;
*/


%token begin endProject setup run define const_kw
%token cst integer float_kw float_signe integer_signe 
%token if_kw then else_kw endIf
%token loop while_kw endloop for_kw in_kw to endfor out affectation
%token add sus mult Div AND OR NON
%token sup_egal inf_egal egal diff sup inf 
%token pointverg deuxpoint barre virgule crochetO crochetF parO parF acolO acolF egg
%token chaine 
%token erreur 
%token <str> idf

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
        {
            if (doubleDeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            } else {
                InsererSymbol(table, $2, $4, "", 0);
            }
        }
        | define idf deuxpoint TYPE egg CONST pointverg
        {
            if (doubleDeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            } else {
                InsererSymbol(table, $2, $4, $6, 0); // 0 is variable
            }
        }
        | define LISTIDF deuxpoint TYPE pointverg
        {
            char *list = strdup($2);
            char *token = strtok(list, "|");
            while(token != NULL) {
                if (doubleDeclaration(token)) {
                    printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", token, nb_ligne, nb_colonne);
                    exit(EXIT_FAILURE);
                } else {
                    InsererSymbol(table, token, $4, "", 0);
                }
                token = strtok(NULL, "|");
            }
            free(list);
        }
        | define LISTIDF deuxpoint TYPE egg CONST pointverg
        {
            char *list = strdup($2);
            char *token = strtok(list, "|");
            while(token != NULL) {
                if (doubleDeclaration(token)) {
                    printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", token, nb_ligne, nb_colonne);
                    exit(EXIT_FAILURE);
                } else {
                    InsererSymbol(table, token, $4, $6, 0); // 0 is variable
                }
                token = strtok(NULL, "|");
            }
            free(list);
        }
        ;
       
// Déclaration d'un Tableau 
DECTABLE : define idf deuxpoint crochetO TYPE pointverg CONST crochetF pointverg
        {
            if (doubleDeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            } else {
                InsererSymbol(table, $2, $5, "", 2);
            }
        }
    ;

// Déclaration d'une Constante 
DECCONST : const_kw idf deuxpoint TYPE egg CONST pointverg
        {
            if (doubleDeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            } else {
                InsererSymbol(table, $2, $4, $6, 1);
            }
        }
    ; 

CONST : cst { $$ = strdup(yytext); }
        | float_signe { $$ = strdup(yytext); }
        | integer_signe { $$ = strdup(yytext); }
        ;


TYPE : integer { $$ = "int"; }
        | float_kw { $$ = "float"; }
        ;

// Déclaration multiple de variables 
LISTIDF : idf barre idf
        {
            $$ = malloc(strlen($1) + strlen($3) + 2);
            sprintf($$, "%s|%s", $1, $3);
        }
        | idf barre LISTIDF
        {
            $$ = malloc(strlen($1) + strlen($3) + 2);
            sprintf($$, "%s|%s", $1, $3);
        }
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
        {
            if (!checkdeclaration($1)) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            } else {
                InfoSymboles *ent = Rechercher(table, $1);
                if (ent->Etat == 1) {
                    printf("Erreur SYMENTIQUE: Modification d'une constante '%s', a la ligne '%d' , et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    exit(EXIT_FAILURE);
                }
                if (strcmp(ent->Type, "int") == 0 && strcmp($3.type, "float") == 0) {
                    printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    exit(EXIT_FAILURE);
                }
            }
        }
        |  idf crochetO cst crochetF affectation EXPR pointverg
        {
            if (!checkdeclaration($1)) {
                printf("Erreur SYMENTIQUE: Non declaration du tableau '%s', a la ligne '%d', et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            }
            InfoSymboles *ent = Rechercher(table, $1);
            if (strcmp(ent->Type, "int") == 0 && strcmp($6.type, "float") == 0) {
                printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un tableau d'int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            }
        }
        |  idf crochetO idf crochetF  affectation EXPR pointverg
        {
            if (!checkdeclaration($1)) {
                printf("Erreur Semantique: %s tableau non declare\n", $1);
                exit(1);
            }
            if (!checkdeclaration($3)) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $3, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            }
            InfoSymboles *ent = Rechercher(table, $1);
            if (strcmp(ent->Type, "int") == 0 && strcmp($6.type, "float") == 0) {
                printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un tableau d'int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            }
        }
        ;


CONDIF : if_kw parO CONDITION parF then deuxpoint acolO INSTRUCTIONS acolF else_kw acolO INSTRUCTIONS acolF endIf pointverg
    | if_kw parO CONDITION parF then deuxpoint acolO INSTRUCTIONS acolF endIf pointverg
    {
    // bool type 
    }
    ;


LECTURE_ECRITURE : out parO chaine virgule EXPR parF pointverg
    | out parO chaine parF pointverg
    | in_kw parO idf parF pointverg
    {
        if (!checkdeclaration($3)) {
            printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $3, nb_ligne, nb_colonne);
            exit(EXIT_FAILURE);
        }
    }
    ;

BOUCLE : loop while_kw parO CONDITION parF acolO INSTRUCTIONS acolF endloop pointverg
        | for_kw idf in_kw CONST to CONST acolO INSTRUCTIONS acolF endfor pointverg
        {
            if (!checkdeclaration($2)) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                exit(EXIT_FAILURE);
            }
        }
        ;

CONDITION : 
    EXPR
        ;

EXPR : EXPR add EXPR
    {
        if (strcmp($1.type, "float") == 0 || strcmp($3.type, "float") == 0) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        strcpy($$.val, "");
    }
    | EXPR sus EXPR     
    {
        if (strcmp($1.type, "float") == 0 || strcmp($3.type, "float") == 0) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        strcpy($$.val, "");
    }
    | EXPR mult EXPR
    {
        if (strcmp($1.type, "float") == 0 || strcmp($3.type, "float") == 0) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        strcpy($$.val, "");
    }
    | EXPR Div EXPR
    {
        if (strcmp($3.val, "0") == 0 || strcmp($3.val, "0.0") == 0 || strcmp($3.val, "(+0)") == 0) {
            printf("Erreur SYMENTIQUE: Division par zero detectee a la ligne '%d' et la colonne '%d' : \n", nb_ligne, nb_colonne);
            exit(EXIT_FAILURE);
        }
        if (strcmp($1.type, "float") == 0 || strcmp($3.type, "float") == 0) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        strcpy($$.val, "");
    }
    | EXPR sup_egal EXPR { strcpy($$.type, ""); }
    | EXPR inf_egal EXPR { strcpy($$.type, ""); }
    | EXPR egal EXPR { strcpy($$.type, ""); }
    | EXPR diff EXPR { strcpy($$.type, ""); }
    | EXPR sup EXPR { strcpy($$.type, ""); }
    | EXPR inf EXPR { strcpy($$.type, ""); }
    | parO EXPR parF { $$ = $2; }
    | idf
    {
        if (!checkdeclaration($1)) {
            printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
            exit(EXIT_FAILURE);
        }
        InfoSymboles *ent = Rechercher(table, $1);
        if(ent) {
            strcpy($$.type, ent->Type);
            strcpy($$.val, ent->Val);
        } else {
            strcpy($$.type, "");
            strcpy($$.val, "");
        }
    }
    | CONST
    {
        if (strchr($1, '.') != NULL) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        strcpy($$.val, $1);
    }
    | chaine { strcpy($$.type, "chaine"); strcpy($$.val, ""); }
    | TAB { strcpy($$.type, $1); strcpy($$.val, ""); }
    | EXPR AND EXPR { strcpy($$.type, ""); strcpy($$.val, ""); }
    | EXPR OR EXPR { strcpy($$.type, ""); strcpy($$.val, ""); }
    | NON EXPR { strcpy($$.type, ""); strcpy($$.val, ""); }
    ;

TAB : idf crochetO EXPR crochetF
    {
        if (!checkdeclaration($1)) {
            printf("Erreur Semantique : tableau %s est non declare\n", $1);
            exit(1);
        }
        InfoSymboles *ent = Rechercher(table, $1);
        if(ent) {
            $$ = ent->Type;
        } else {
            $$ = "";
        }
    }





%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erreur Syntaxique, ligne %d, colonne %d, entite : %s\n", nb_ligne, nb_colonne, yytext, msg);
}

int main() {
    table = createHashTable(50);
    printf("Lancement Analyse Syntaxique\n");
    if (yyparse() == 0) {
        printf("Analyse syntaxique correcte\n");
        AfficherTableHG(table);
    }
    return 0;
}
