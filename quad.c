#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"

// Variables globales
#define QUAD_CAPACITE_INITIALE 256
qdr *quad = NULL;
int qc = 0;
static int quad_capacite = 0;

/* Initialise (ou re-verifie) l'allocation du tableau de quadruplets */
static void quad_assurer_capacite()
{
    if (quad == NULL) {
        quad = malloc(sizeof(qdr) * QUAD_CAPACITE_INITIALE);
        if (!quad) { fprintf(stderr, "Erreur : allocation quadruplets\n"); exit(1); }
        quad_capacite = QUAD_CAPACITE_INITIALE;
    }
    if (qc >= quad_capacite) {
        quad_capacite *= 2;
        quad = realloc(quad, sizeof(qdr) * quad_capacite);
        if (!quad) { fprintf(stderr, "Erreur : reallocation quadruplets\n"); exit(1); }
    }
}

/* 1- Fonction d'ajout d'un quadruplet a une table de quadruplets */
void quadr(char opr[], char op1[], char op2[], char res[])
{
    quad_assurer_capacite();
    strcpy(quad[qc].oper, opr);
    strcpy(quad[qc].op1, op1);
    strcpy(quad[qc].op2, op2);
    strcpy(quad[qc].res, res);
    qc++;
}

/* 2- Fonction qui permet de mettre a jour les quadruplets 
selon la position : (0,1,2,3) 
*/
void updateQuad(int num_quad, int colon_quad, char val[])
{
    if (num_quad < 0 || num_quad >= qc) {
        fprintf(stderr, "Erreur updateQuad : index %d hors bornes [0..%d]\n", num_quad, qc - 1);
        return;
    }
    if (colon_quad == 0) strcpy(quad[num_quad].oper, val);
    else if (colon_quad == 1) strcpy(quad[num_quad].op1, val);
    else if (colon_quad == 2) strcpy(quad[num_quad].op2, val);
    else if (colon_quad == 3) strcpy(quad[num_quad].res, val);
}

/* Fonction d'affichage des quadruplets generes */
void afficher_qdr()
{
    printf("********************* Les Quadruplets ***********************\n");
    printf("_____________________________________________________________\n");
    int i;
    for(i = 0; i < qc; i++)
    {
        printf("\n %d - ( %s  ,  %s  ,  %s  ,  %s )", i, quad[i].oper, quad[i].op1, quad[i].op2, quad[i].res); 
        printf("\n--------------------------------------------------------\n");
    }
}

// Quadruplets pour les expressions logiques d = b OP c
void quadL(int type, char* b, char* c, char* d){
    char etiquette[15]; // Pour stocker dynamiquement le numero de branchement (qc)
    switch(type){
        case 1 : // AND: d = b AND c
            /* 
             * Explication du branchement pour b AND c :
             * - BZ (Branch if Zero) : Si b est faux (0), on saute vers la ligne `qc + 4` où d sera mis à 0.
             * - BZ : Si c est faux (0), on saute aussi vers `qc + 3` où d sera mis à 0.
             * - Sinon, b et c sont vrais, on met d à 1.
             * - BR (Branch) : Saut inconditionnel vers la fin `qc + 2` pour eviter la ligne d = 0.
             * - A la fin, la ligne `d = 0` est la cible de saut pour faux.
             */
            sprintf(etiquette, "%d", qc + 4); quadr("BZ", etiquette, b, ""); 
            sprintf(etiquette, "%d", qc + 3); quadr("BZ", etiquette, c, ""); 
            quadr("=", "1", "", d); 
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", ""); 
            quadr("=", "0", "", d); 
        break;
        case 2 : // OR: d = b OR c
            /* 
             * Explication du branchement pour b OR c :
             * - BNZ (Branch if Not Zero) : Si b est vrai (≠ 0), on saute directement vers `qc + 4` où d = 1.
             * - BNZ : Si c est vrai (≠ 0), on saute aussi vers `qc + 3` où d = 1.
             * - Sinon, b et c sont faux, on met d à 0.
             * - BR (Branch) : Saut inconditionnel vers la fin `qc + 2` pour eviter la ligne d = 1.
             */
            sprintf(etiquette, "%d", qc + 4); quadr("BNZ", etiquette, b, ""); 
            sprintf(etiquette, "%d", qc + 3); quadr("BNZ", etiquette, c, ""); 
            quadr("=", "0", "", d); 
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", ""); 
            quadr("=", "1", "", d); 
        break;
        case 3 : // NOT: d = NON b
            /*
             * Explication du branchement pour NOT b :
             * - BZ (Branch if Zero) : Si b est faux (0), on saute vers `qc + 3` où d = 1 (NOT 0 = 1).
             * - Sinon, on met d à 0.
             * - BR : on saute la ligne d = 1.
             */
            sprintf(etiquette, "%d", qc + 3); quadr("BZ", etiquette, b, "");
            quadr("=", "0", "", d);
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", "");
            quadr("=", "1", "", d);
        break;
    }
}

// Quadruplets pour les expressions de comparaison d = b OP c
void quadC(int type, char* b, char* c, char* d){
    char etiquette[15];
    switch(type){
        case 1 : // > (Superieur)
            /* 
             * Explication pour (b > c) :
             * - On effectue la soustraction b - c et on stocke le resultat temporaire dans d.
             * - BG (Branch if Greater) : Si d > 0 (donc b > c), on saute vers `qc + 3` où d = 1 (vrai).
             * - Sinon, d = 0 (faux).
             * - BR : Saut inconditionnel pour eviter la ligne d = 1.
             */
            quadr("-", b, c, d); 
            sprintf(etiquette, "%d", qc + 3); quadr("BG", etiquette, d, "");
            quadr("=", "0", "", d);
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", "");
            quadr("=", "1", "", d);
        break;
        case 2 : // >= (Superieur ou egal)
            /* Explication: Pareil, BGE (Branch if Greater or Equal) verifie si (b - c) >= 0 */
            quadr("-", b, c, d); 
            sprintf(etiquette, "%d", qc + 3); quadr("BGE", etiquette, d, "");
            quadr("=", "0", "", d);
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", "");
            quadr("=", "1", "", d);
        break;
        case 3 : // < (Inferieur)
            /* Explication: BL (Branch if Less) verifie si (b - c) < 0 */
            quadr("-", b, c, d); 
            sprintf(etiquette, "%d", qc + 3); quadr("BL", etiquette, d, "");
            quadr("=", "0", "", d);
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", "");
            quadr("=", "1", "", d);
        break;
        case 4 : // <= (Inferieur ou egal)
            /* Explication: BLE (Branch if Less or Equal) verifie si (b - c) <= 0 */
            quadr("-", b, c, d); 
            sprintf(etiquette, "%d", qc + 3); quadr("BLE", etiquette, d, "");
            quadr("=", "0", "", d);
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", "");
            quadr("=", "1", "", d);
        break;
        case 5 : // == (Egal)
            /* Explication: BZ (Branch if Zero) verifie si (b - c) == 0 (donc b = c) */
            quadr("-", b, c, d); 
            sprintf(etiquette, "%d", qc + 3); quadr("BZ", etiquette, d, "");
            quadr("=", "0", "", d);
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", "");
            quadr("=", "1", "", d);
        break;
        case 6 : // != (Different)
            /* Explication: BNZ (Branch if Not Zero) verifie si (b - c) != 0 (donc b != c) */
            quadr("-", b, c, d); 
            sprintf(etiquette, "%d", qc + 3); quadr("BNZ", etiquette, d, "");
            quadr("=", "0", "", d);
            sprintf(etiquette, "%d", qc + 2); quadr("BR", etiquette, "", "");
            quadr("=", "1", "", d);
        break;
    }
}