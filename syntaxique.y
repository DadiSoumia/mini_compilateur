%{
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

%}


// types

%union {
    char* str;   // Pour transporter des noms d'identifiants ou des types
    struct {
        char type[20]; // Pour stocker le type d'une expression (int/float)
        char val[50];  // Pour stocker la valeur textuelle d'une expression
    } expr;
}

%type <str> TYPE CONST LISTIDF
%type <expr> TAB
%type <expr> EXPR


%token begin endProject setup run define const_kw
%token integer float_kw
%token if_kw then else_kw endIf
%token loop while_kw endloop for_kw in_kw to endfor out in_put affectation
%token add sus mult Div AND OR NON
%token sup_egal inf_egal egal diff sup inf 
%token pointverg deuxpoint barre virgule crochetO crochetF parO parF acolO acolF egg

%token erreur 
%token <str> idf cst float_signe integer_signe chaine



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
            if (checkdeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, $2, $4, "", 0);
            }
        }

        | define idf deuxpoint TYPE egg CONST pointverg
        {
            if (checkdeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, $2, $4, $6, 0); // 0 is variable
            }
        }

        | define LISTIDF deuxpoint TYPE pointverg
        {
            // Pour les listes (a|b|c), on utilise la chaîne déjà allouée
            char *list = $2;
            char *token = strtok(list, "|");  // On sépare par le caractère '|'

            while(token != NULL) {
                if (checkdeclaration(token)) {
                    printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", token, nb_ligne, nb_colonne);
                 
                } else {
                    InsererSymbol(table, token, $4, "", 0);
                }
                token = strtok(NULL, "|");
            }
            free(list);
        }
        | define LISTIDF deuxpoint TYPE egg CONST pointverg
        {
            char *list = $2;
            char *token = strtok(list, "|");

            while(token != NULL) {
                if (checkdeclaration(token)) {
                    printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", token, nb_ligne, nb_colonne);
                    
                    
                } else {
                    InsererSymbol(table, token, $4, $6, 0); // 0 is variable
                }
                token = strtok(NULL, "|"); // Passe à l'identifiant suivant
            }
            free(list);
        }
        ;
       
// Déclaration d'un Tableau 
DECTABLE : define idf deuxpoint crochetO TYPE pointverg CONST crochetF pointverg
        {
            if (checkdeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne); 
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, $2, $5, "", 2);
            }
        }

    ;

// Déclaration d'une Constante 
DECCONST : const_kw idf deuxpoint TYPE egg CONST pointverg
        {
            if (checkdeclaration($2)) {
                printf("Erreur SYMENTIQUE: Double declaration de l'identifiant '%s', a la ligne '%d' , et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InsererSymbol(table, $2, $4, $6, 1);
            }
        }

    ; 

CONST : cst { $$ = $1; }
        | float_signe { $$ = $1; }
        | integer_signe { $$ = $1; }
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
                nb_erreur_sem++;
            } else {
                InfoSymboles *ent = Rechercher(table, $1);
                int has_error = 0;
                if (ent->Etat == 1) {
                    printf("Erreur SYMENTIQUE: Modification d'une constante '%s', a la ligne '%d' , et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (strcmp(ent->Type, "int") == 0 && strcmp($3.type, "float") == 0) {
                    printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (!has_error) {
                    MettreAJourSymbol(table, $1, $3.val, NULL, ent->Etat);
                    quadr("=", $3.val, "", $1);
                }
            }
        }


        |  idf crochetO cst crochetF affectation EXPR pointverg
        {
            if (!checkdeclaration($1)) {
                printf("Erreur SYMENTIQUE: Non declaration du tableau '%s', a la ligne '%d', et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InfoSymboles *ent = Rechercher(table, $1);
                int has_error = 0;
                if (ent->Etat == 1) {
                    printf("Erreur SYMENTIQUE: Modification d'une constante '%s', a la ligne '%d' , et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (strcmp(ent->Type, "int") == 0 && strcmp($6.type, "float") == 0) {
                    printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un tableau d'int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (!has_error) {
                    MettreAJourSymbol(table, $1, $6.val, NULL, ent->Etat);
                    char tmp_arr[50];
                    sprintf(tmp_arr, "%s[%s]", $1, $3);
                    quadr("=", $6.val, "", tmp_arr);
                }
            }
        }


        |  idf crochetO idf crochetF  affectation EXPR pointverg
        {
            if (!checkdeclaration($1)) {
                printf("Erreur Semantique: %s tableau non declare\n", $1);
                nb_erreur_sem++;
            } else if (!checkdeclaration($3)) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $3, nb_ligne, nb_colonne);
                nb_erreur_sem++;
            } else {
                InfoSymboles *ent = Rechercher(table, $1);
                int has_error = 0;
                if (ent->Etat == 1) {
                    printf("Erreur SYMENTIQUE: Modification d'une constante '%s', a la ligne '%d' , et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (strcmp(ent->Type, "int") == 0 && strcmp($6.type, "float") == 0) {
                    printf("Erreur SYMENTIQUE: Incompatibilite de type lors de l'affectation a '%s' (un tableau d'int ne peut pas recevoir un float) a la ligne '%d' et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
                    nb_erreur_sem++;
                    has_error = 1;
                }
                if (!has_error) {
                    MettreAJourSymbol(table, $1, $6.val, NULL, ent->Etat);
                    char tmp_arr[50];
                    sprintf(tmp_arr, "%s[%s]", $1, $3);
                    quadr("=", $6.val, "", tmp_arr);
                }
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
    | in_put parO idf parF pointverg
    {
        if (!checkdeclaration($3)) {
            printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $3, nb_ligne, nb_colonne);
            nb_erreur_sem++;
        }
    }

    ;

BOUCLE : loop while_kw parO CONDITION parF acolO INSTRUCTIONS acolF endloop pointverg
        | for_kw idf in_kw CONST to CONST acolO INSTRUCTIONS acolF endfor pointverg
        {
            if (!checkdeclaration($2)) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                nb_erreur_sem++;
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
        sprintf($$.val, "T%d", temp_var_count++);
        quadr("+", $1.val, $3.val, $$.val);
    }
    | EXPR sus EXPR     
    {
        if (strcmp($1.type, "float") == 0 || strcmp($3.type, "float") == 0) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        sprintf($$.val, "T%d", temp_var_count++);
        quadr("-", $1.val, $3.val, $$.val);
    }
    | EXPR mult EXPR
    {
        if (strcmp($1.type, "float") == 0 || strcmp($3.type, "float") == 0) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        sprintf($$.val, "T%d", temp_var_count++);
        quadr("*", $1.val, $3.val, $$.val);
    }
    | EXPR Div EXPR
    {
        if (strcmp($3.val, "0") == 0 || strcmp($3.val, "0.0") == 0 || strcmp($3.val, "(+0)") == 0) {
            printf("Erreur SYMENTIQUE: Division par zero detectee a la ligne '%d' et la colonne '%d' : \n", nb_ligne, nb_colonne);
            nb_erreur_sem++;
        }
        if (strcmp($1.type, "float") == 0 || strcmp($3.type, "float") == 0) strcpy($$.type, "float");
        else strcpy($$.type, "int");
        sprintf($$.val, "T%d", temp_var_count++);
        quadr("/", $1.val, $3.val, $$.val);
    }

    | EXPR sup_egal EXPR { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadC(2, $1.val, $3.val, $$.val); }
    | EXPR inf_egal EXPR { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadC(4, $1.val, $3.val, $$.val); }
    | EXPR egal EXPR     { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadC(5, $1.val, $3.val, $$.val); }
    | EXPR diff EXPR     { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadC(6, $1.val, $3.val, $$.val); }
    | EXPR sup EXPR      { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadC(1, $1.val, $3.val, $$.val); }
    | EXPR inf EXPR      { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadC(3, $1.val, $3.val, $$.val); }
    | parO EXPR parF { $$ = $2; }
    | idf
    {
        if (!checkdeclaration($1)) {
            printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $1, nb_ligne, nb_colonne);
           
        }
        InfoSymboles *ent = Rechercher(table, $1);
        if(ent) {
            strcpy($$.type, ent->Type);
            strcpy($$.val, $1);
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
    | chaine { strcpy($$.type, "chaine"); strcpy($$.val, $1); }

    | TAB { strcpy($$.type, $1.type); strcpy($$.val, $1.val); }
    | EXPR AND EXPR { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadL(1, $1.val, $3.val, $$.val); }
    | EXPR OR EXPR  { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadL(2, $1.val, $3.val, $$.val); }
    | NON EXPR      { strcpy($$.type, "int"); sprintf($$.val, "T%d", temp_var_count++); quadL(3, $2.val, "", $$.val); }
    ;

TAB : idf crochetO EXPR crochetF
    {
        if (!checkdeclaration($1)) {
            printf("Erreur Semantique : tableau %s est non declare\n", $1);
           
        }
        InfoSymboles *ent = Rechercher(table, $1);
        if(ent) {
            strcpy($$.type, ent->Type);
            sprintf($$.val, "%s[%s]", $1, $3.val);
        } else {
            strcpy($$.type, "");
            strcpy($$.val, "");
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
