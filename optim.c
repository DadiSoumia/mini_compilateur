#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"
#include "optim.h"

void simplification_algebrique();
void propagation_constante();
void propagation_copie();
void elimination_redondantes();
void elimination_code_inutile();
void afficher_qdr_optimise();
void optimiser();

static int est_branchement(const char *op)
{
    return (strncmp(op, "B", 1) == 0 && strlen(op) >= 2);
}

static int est_temporaire(const char *nom)
{
    return (nom[0] == 'T' && nom[1] >= '0' && nom[1] <= '9');
}

static int est_actif(int i)
{
    return (strcmp(quad[i].oper, "NOP") != 0 && strcmp(quad[i].oper, "") != 0);
}

static int contient_temporaire(const char *chaine, const char *res)
{
    char *pos = strstr(chaine, res);
    if (pos == NULL)
        return 0;

    int len = strlen(res);
    char apres = pos[len];
    if (apres >= '0' && apres <= '9')
        return 0;

    return 1;
}

static void remplacer_dans_operandes(int start, const char *ancien, const char *nouveau)
{

    if (!est_temporaire(ancien))
        return;

    for (int i = start; i < qc; i++)
    {
        if (!est_actif(i))
            continue;

        if (strcmp(quad[i].res, ancien) == 0)
            break;
        if (strcmp(quad[i].res, nouveau) == 0)
            break;

        if (strcmp(quad[i].op1, ancien) == 0)
            strcpy(quad[i].op1, nouveau);
        if (strcmp(quad[i].op2, ancien) == 0)
            strcpy(quad[i].op2, nouveau);
    }
}

static int est_constante(const char *s)
{
    if (s == NULL || strlen(s) == 0)
        return 0;
    int i = 0;
    if (s[i] == '-')
        i++;
    if (s[i] == '\0')
        return 0;
    int a_chiffre = 0;
    while (s[i] >= '0' && s[i] <= '9')
    {
        a_chiffre = 1;
        i++;
    }
    if (s[i] == '.')
    {
        i++;
        while (s[i] >= '0' && s[i] <= '9')
            i++;
    }
    return (a_chiffre && s[i] == '\0');
}

void simplification_algebrique()
{
    for (int i = 0; i < qc; i++)
    {
        if (!est_actif(i))
            continue;

        const char *op = quad[i].oper;
        char *op1 = quad[i].op1;
        char *op2 = quad[i].op2;
        char *res = quad[i].res;

        if (strcmp(op, "+") == 0)
        {
            if (est_constante(op2) && atof(op2) == 0.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }
            else if (est_constante(op1) && atof(op1) == 0.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, op2);
                strcpy(quad[i].op2, "");
            }
        }

        else if (strcmp(op, "-") == 0)
        {
            if (est_constante(op2) && atof(op2) == 0.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }
            else if (strcmp(op1, op2) == 0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, "0");
                strcpy(quad[i].op2, "");
            }
        }

        else if (strcmp(op, "*") == 0)
        {
            if ((est_constante(op1) && atof(op1) == 0.0) ||
                (est_constante(op2) && atof(op2) == 0.0))
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, "0");
                strcpy(quad[i].op2, "");
            }
            else if (est_constante(op2) && atof(op2) == 1.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }
            else if (est_constante(op1) && atof(op1) == 1.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, op2);
                strcpy(quad[i].op2, "");
            }
        }

        else if (strcmp(op, "/") == 0)
        {

            if (est_constante(op2) && atof(op2) == 1.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }

            else if (est_constante(op1) && atof(op1) == 0.0 &&
                     !(est_constante(op2) && atof(op2) == 0.0))
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, "0");
                strcpy(quad[i].op2, "");
            }
        }
    }
}

void propagation_constante()
{
    for (int i = 0; i < qc; i++)
    {
        if (!est_actif(i))
            continue;

        if (strcmp(quad[i].oper, "=") != 0)
            continue;
        if (strcmp(quad[i].op2, "") != 0)
            continue;

        const char *cste = quad[i].op1;
        const char *var = quad[i].res;

        if (!est_constante(cste))
            continue;

        if (strlen(var) == 0)
            continue;

        for (int j = i + 1; j < qc; j++)
        {
            if (!est_actif(j))
                continue;

            if (strcmp(quad[j].res, var) == 0)
                break;

            int j_est_branchement = est_branchement(quad[j].oper);

            if (!j_est_branchement && strcmp(quad[j].op1, var) == 0)
                strcpy(quad[j].op1, cste);

            if (strcmp(quad[j].op2, var) == 0)
                strcpy(quad[j].op2, cste);
        }
    }
}

void propagation_copie()
{
    for (int i = 0; i < qc; i++)
    {
        if (!est_actif(i))
            continue;

        if (strcmp(quad[i].oper, "=") == 0 && strcmp(quad[i].op2, "") == 0)
        {
            const char *source = quad[i].op1;
            const char *cible = quad[i].res;

            if (strlen(source) == 0 || strcmp(source, cible) == 0)
                continue;

            if (!est_temporaire(source))
                continue;

            remplacer_dans_operandes(i + 1, cible, source);
        }
    }
}

static int est_modifie_entre(const char *nom, int from, int to)
{
    for (int k = from; k < to; k++)
    {
        if (!est_actif(k))
            continue;
        if (strcmp(quad[k].res, nom) == 0)
            return 1;
    }
    return 0;
}

static int est_commutatif(const char *op)
{
    return (strcmp(op, "+") == 0 || strcmp(op, "*") == 0);
}

void elimination_redondantes()
{
    for (int i = 0; i < qc; i++)
    {
        if (!est_actif(i))
            continue;
        if (strcmp(quad[i].oper, "=") == 0)
            continue;
        if (est_branchement(quad[i].oper))
            continue;
        if (strcmp(quad[i].res, "") == 0)
            continue;

        for (int j = i + 1; j < qc; j++)
        {
            if (!est_actif(j))
                continue;
            if (strcmp(quad[j].oper, quad[i].oper) != 0)
                continue;

            int meme_ordre = (strcmp(quad[j].op1, quad[i].op1) == 0 &&
                              strcmp(quad[j].op2, quad[i].op2) == 0);
            int ordre_comm = est_commutatif(quad[i].oper) &&
                             (strcmp(quad[j].op1, quad[i].op2) == 0 &&
                              strcmp(quad[j].op2, quad[i].op1) == 0);

            if (!meme_ordre && !ordre_comm)
                continue;

            if (strlen(quad[i].op1) > 0 && est_modifie_entre(quad[i].op1, i + 1, j))
                continue;
            if (strlen(quad[i].op2) > 0 && est_modifie_entre(quad[i].op2, i + 1, j))
                continue;

            strcpy(quad[j].oper, "=");
            strcpy(quad[j].op1, quad[i].res);
            strcpy(quad[j].op2, "");
        }
    }
}

void elimination_code_inutile()
{
    for (int i = 0; i < qc; i++)
    {
        if (!est_actif(i))
            continue;

        const char *res = quad[i].res;

        if (strlen(res) == 0)
            continue;

        if (!est_temporaire(res))
            continue;

        int utilise = 0;
        for (int j = 0; j < qc; j++)
        {
            if (i == j)
                continue;
            if (!est_actif(j))
                continue;

            if (contient_temporaire(quad[j].op1, res) ||
                contient_temporaire(quad[j].op2, res) ||
                contient_temporaire(quad[j].res, res))
            {
                utilise = 1;
                break;
            }
        }

        if (!utilise)
        {
            strcpy(quad[i].oper, "NOP");
            strcpy(quad[i].op1, "");
            strcpy(quad[i].op2, "");
            strcpy(quad[i].res, "");
        }
    }
}

void afficher_qdr_optimise()
{
    printf("\n************* Quadruplets Optimises *****************\n");
    printf("_____________________________________________________________\n");
    int affiche = 0;
    for (int i = 0; i < qc; i++)
    {
        if (strcmp(quad[i].oper, "NOP") == 0 || strcmp(quad[i].oper, "") == 0)
            continue;
        printf("\n %d - ( %s  ,  %s  ,  %s  ,  %s )",
               i, quad[i].oper, quad[i].op1, quad[i].op2, quad[i].res);
        printf("\n--------------------------------------------------------\n");
        affiche++;
    }
    if (affiche == 0)
        printf("  (aucun quadruplet actif)\n");
}

void optimiser()
{
    printf("\n============================================================\n");
    printf("           OPTIMISATION DU CODE INTERMEDIAIRE\n");
    printf("============================================================\n");

    simplification_algebrique();
    propagation_constante();
    propagation_copie();
    elimination_redondantes();
    elimination_code_inutile();

    simplification_algebrique();
    propagation_constante();
    propagation_copie();
    elimination_redondantes();
    elimination_code_inutile();

    afficher_qdr_optimise();
}