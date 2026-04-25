%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int val_int; // Pour la gestion des quadruplets (backpatching)
}

%type <str> TYPE CONST LISTIDF
%type <expr> TAB
%type <expr> EXPR
%type <expr> CONDITION
%type <val_int> M 
%type <val_int> N
%type <val_int> M_cond


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
                    if ($3.val[0] != 'T') {
                        MettreAJourSymbol(table, $1, $3.val, NULL, ent->Etat);
                    }
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
                    if ($6.val[0] != 'T') {
                        MettreAJourSymbol(table, $1, $6.val, NULL, ent->Etat);
                    }
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
                    if ($6.val[0] != 'T') {
                        MettreAJourSymbol(table, $1, $6.val, NULL, ent->Etat);
                    }
                    char tmp_arr[50];
                    sprintf(tmp_arr, "%s[%s]", $1, $3);
                    quadr("=", $6.val, "", tmp_arr);
                }
            }
        }


        ;


CONDIF : if_kw parO M_cond parF then deuxpoint acolO INSTRUCTIONS acolF endIf pointverg
        {
            char temp[20];
            sprintf(temp, "%d", qc); 
            // On met à jour le BZ (généré par M_cond) pour qu'il saute à la fin (qc actuel)
            updateQuad($3, 1, temp); 
        }
       | if_kw parO M_cond parF then deuxpoint acolO INSTRUCTIONS acolF N else_kw acolO M INSTRUCTIONS acolF endIf pointverg
        {
            char temp[20];
            // Mettre à jour le BZ de la condition pour qu'il saute au début du bloc ELSE (sauvegardé dans M)
            sprintf(temp, "%d", $13);
            updateQuad($3, 1, temp);

            // Mettre à jour le BR (généré par N à la fin du INSTRUCTIONS1) pour qu'il saute complètement a la fin du IF
            sprintf(temp, "%d", qc);
            updateQuad($10, 1, temp);
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

BOUCLE : loop while_kw parO M M_cond parF acolO INSTRUCTIONS acolF endloop pointverg
        {
            char temp[20];
            
            // Quad pour revenir revérifier la condition en haut (M = $4)
            sprintf(temp, "%d", $4);
            quadr("BR", temp, "", "");
            
            // Mettre à jour le BZ de sortie de boucle (généré par M_cond, qui est $5) pour aller à la fin de la boucle
            sprintf(temp, "%d", qc);
            updateQuad($5, 1, temp);
        }
        
       | for_kw idf in_kw CONST to CONST acolO 
        {
            if (!checkdeclaration($2)) {
                printf("Erreur SYMENTIQUE: Non declaration de l'identifiant '%s', a la ligne '%d', et la colonne '%d' : \n", $2, nb_ligne, nb_colonne);
                nb_erreur_sem++;
            }
            // 1. Initialisation var = CONST1
            quadr("=", $4, "", $2);

            // 2. Sauvegarde du debut de l'évaluation conditionnelle
            $<val_int>$ = qc; // devient le token $8
        }
        {
            // 3. Evaluation condition : idf <= CONST2
            char cond[20];
            sprintf(cond, "T%d", temp_var_count++);
            quadC(4, $<str>2, $<str>6, cond); 
            
            // 4. Sauvegarde de l'adresse du BZ
            $<val_int>$ = qc; // devient le token $9
            quadr("BZ", "", cond, "");
        }
        INSTRUCTIONS acolF endfor pointverg
        {
            char temp[20];
            
            // 5. Incrementation interne a la fin du bloc: idf = idf + 1
            char t_inc[20];
            sprintf(t_inc, "T%d", temp_var_count++);
            quadr("+", $<str>2, "1", t_inc);
            quadr("=", t_inc, "", $<str>2);

            // 6. Saut vers l'évaluation de la condition (le token $8)
            sprintf(temp, "%d", $<val_int>8);
            quadr("BR", temp, "", "");

            // 7. Update BZ ($9) pour sauter a la fin après la boucle
            sprintf(temp, "%d", qc);
            updateQuad($<val_int>9, 1, temp);
        }
    ;

CONDITION : 
    EXPR { $$ = $1; }
    ;

M : { $$ = qc; } ;

N : { $$ = qc; quadr("BR", "", "", ""); } ;

M_cond : CONDITION {
    $$ = qc; // on sauvegarde l'index du quadruplet qui contiendra le 'BZ'
    quadr("BZ", "", $1.val, ""); // On a pas de destination encore, op1 est vide ("")
} ;


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
