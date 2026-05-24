#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"

#define QUAD_CAPACITE_INITIALE 256
qdr *quad = NULL;
int qc = 0;
static int quad_capacite = 0;

static void quad_assurer_capacite()
{
    if (quad == NULL)
    {
        quad = malloc(sizeof(qdr) * QUAD_CAPACITE_INITIALE);
        if (!quad)
        {
            fprintf(stderr, "Erreur : allocation quadruplets\n");
            exit(1);
        }
        quad_capacite = QUAD_CAPACITE_INITIALE;
    }
    if (qc >= quad_capacite)
    {
        quad_capacite *= 2;
        quad = realloc(quad, sizeof(qdr) * quad_capacite);
        if (!quad)
        {
            fprintf(stderr, "Erreur : reallocation quadruplets\n");
            exit(1);
        }
    }
}

void quadr(char opr[], char op1[], char op2[], char res[])
{
    quad_assurer_capacite();
    strcpy(quad[qc].oper, opr);
    strcpy(quad[qc].op1, op1);
    strcpy(quad[qc].op2, op2);
    strcpy(quad[qc].res, res);
    qc++;
}

void updateQuad(int num_quad, int colon_quad, char val[])
{
    if (num_quad < 0 || num_quad >= qc)
    {
        fprintf(stderr, "Erreur updateQuad : index %d hors bornes [0..%d]\n", num_quad, qc - 1);
        return;
    }
    if (colon_quad == 0)
        strcpy(quad[num_quad].oper, val);
    else if (colon_quad == 1)
        strcpy(quad[num_quad].op1, val);
    else if (colon_quad == 2)
        strcpy(quad[num_quad].op2, val);
    else if (colon_quad == 3)
        strcpy(quad[num_quad].res, val);
}

void afficher_qdr()
{
    printf("********************* Les Quadruplets ***********************\n");
    printf("_____________________________________________________________\n");
    int i;
    for (i = 0; i < qc; i++)
    {
        printf("\n %d - ( %s  ,  %s  ,  %s  ,  %s )", i, quad[i].oper, quad[i].op1, quad[i].op2, quad[i].res);
        printf("\n--------------------------------------------------------\n");
    }
}

void quadL(int type, char *b, char *c, char *d)
{
    char etiquette[15];
    switch (type)
    {
    case 1:

        sprintf(etiquette, "%d", qc + 4);
        quadr("BZ", etiquette, b, "");
        sprintf(etiquette, "%d", qc + 3);
        quadr("BZ", etiquette, c, "");
        quadr("=", "1", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "0", "", d);
        break;
    case 2:
        sprintf(etiquette, "%d", qc + 4);
        quadr("BNZ", etiquette, b, "");
        sprintf(etiquette, "%d", qc + 3);
        quadr("BNZ", etiquette, c, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    case 3:
        sprintf(etiquette, "%d", qc + 3);
        quadr("BZ", etiquette, b, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    }
}

void quadC(int type, char *b, char *c, char *d)
{
    char etiquette[15];
    switch (type)
    {
    case 1:
        quadr("-", b, c, d);
        sprintf(etiquette, "%d", qc + 3);
        quadr("BG", etiquette, d, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    case 2:
        quadr("-", b, c, d);
        sprintf(etiquette, "%d", qc + 3);
        quadr("BGE", etiquette, d, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    case 3:
        quadr("-", b, c, d);
        sprintf(etiquette, "%d", qc + 3);
        quadr("BL", etiquette, d, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    case 4:
        quadr("-", b, c, d);
        sprintf(etiquette, "%d", qc + 3);
        quadr("BLE", etiquette, d, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    case 5:
        quadr("-", b, c, d);
        sprintf(etiquette, "%d", qc + 3);
        quadr("BZ", etiquette, d, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    case 6:
        quadr("-", b, c, d);
        sprintf(etiquette, "%d", qc + 3);
        quadr("BNZ", etiquette, d, "");
        quadr("=", "0", "", d);
        sprintf(etiquette, "%d", qc + 2);
        quadr("BR", etiquette, "", "");
        quadr("=", "1", "", d);
        break;
    }
}