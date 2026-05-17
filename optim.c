#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"
#include "optim.h"

/* ============================================================
 *  UTILITAIRES INTERNES
 * ============================================================ */

/* Retourne 1 si l'opérateur est un branchement (BR, BZ, BNZ, BG...) */
static int est_branchement(const char *op)
{
    return (strncmp(op, "B", 1) == 0 && strlen(op) >= 2);
}

/* Retourne 1 si la variable est une temporaire générée (commence par T + chiffre) */
static int est_temporaire(const char *nom)
{
    return (nom[0] == 'T' && nom[1] >= '0' && nom[1] <= '9');
}

/* Retourne 1 si le quadruplet i est actif (pas NOP, pas vide) */
static int est_actif(int i)
{
    return (strcmp(quad[i].oper, "NOP") != 0 && strcmp(quad[i].oper, "") != 0);
}

/* Remplace toutes les occurrences de 'ancien' par 'nouveau'
   dans op1 et op2 des quadruplets de start à qc-1,
   en s'arrêtant dès que 'ancien' ou 'nouveau' est réassigné (res). */
static void remplacer_dans_operandes(int start, const char *ancien, const char *nouveau)
{
    /* ✅ AJOUT : on ne propage pas si 'ancien' est une variable utilisateur */
    /* (une variable utilisateur = pas une temporaire)                       */
    /* car elle peut etre lue directement dans output, input, etc.           */
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
/* ============================================================
 *  1. PROPAGATION DE COPIE
 *  Si on trouve  (= , X , , Y)  →  on remplace Y par X
 *  dans les quadruplets suivants (tant que ni X ni Y
 *  ne sont réassignés).
 * ============================================================ */
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

            /* ✅ AJOUT : on ne propage que si la SOURCE est une temporaire */
            /* Cela evite de remplacer x par 5 partout                      */
            if (!est_temporaire(source))
                continue;

            remplacer_dans_operandes(i + 1, cible, source);
        }
    }
}

/* ============================================================
 *  2. ÉLIMINATION DES EXPRESSIONS REDONDANTES
 *  Si deux quadruplets ont le même opérateur + mêmes opérandes
 *  et qu'aucun des opérandes n'est modifié entre les deux,
 *  on remplace le 2e par une copie du résultat du 1er.
 * ============================================================ */

/* Retourne 1 si 'nom' est réassigné (apparaît dans res) entre from et to */
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

/* Retourne 1 si les deux opérateurs sont commutatifs */
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
        /* Ignorer les affectations simples, les NOP, les branchements */
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

            /* Vérifier si op1/op2 correspondent (ordre normal ou commutatif) */
            int meme_ordre = (strcmp(quad[j].op1, quad[i].op1) == 0 &&
                              strcmp(quad[j].op2, quad[i].op2) == 0);
            int ordre_comm = est_commutatif(quad[i].oper) &&
                             (strcmp(quad[j].op1, quad[i].op2) == 0 &&
                              strcmp(quad[j].op2, quad[i].op1) == 0);

            if (!meme_ordre && !ordre_comm)
                continue;

            /* Vérifier qu'aucun des opérandes n'a été modifié entre i et j */
            if (strlen(quad[i].op1) > 0 && est_modifie_entre(quad[i].op1, i + 1, j))
                continue;
            if (strlen(quad[i].op2) > 0 && est_modifie_entre(quad[i].op2, i + 1, j))
                continue;

            /* Remplacer le quadruplet j par une copie : (= , res_i , , res_j) */
            strcpy(quad[j].oper, "=");
            strcpy(quad[j].op1, quad[i].res);
            strcpy(quad[j].op2, "");
            /* quad[j].res reste inchangé */
        }
    }
}

/* ============================================================
 *  3. ÉLIMINATION DU CODE MORT (code inutile)
 *  Un quadruplet est inutile si son résultat :
 *   - est une temporaire (commence par T)
 *   - n'apparaît jamais dans op1 ou op2 d'un autre quadruplet
 *  On le marque NOP.
 * ============================================================ */
void elimination_code_inutile()
{
    for (int i = 0; i < qc; i++)
    {
        if (!est_actif(i))
            continue;

        const char *res = quad[i].res;

        /* On ne supprime pas les quadruplets sans résultat (output, input, BR...) */
        if (strlen(res) == 0)
            continue;

        /* On ne supprime que les temporaires (T0, T1, ...) */
        if (!est_temporaire(res))
            continue;

        /* Vérifier si ce résultat est utilisé quelque part */
        int utilise = 0;
        for (int j = 0; j < qc; j++)
        {
            if (i == j)
                continue;
            if (!est_actif(j))
                continue;
            if (strcmp(quad[j].op1, res) == 0 || strcmp(quad[j].op2, res) == 0)
            {
                utilise = 1;
                break;
            }
            /* Aussi vérifier dans res (cas d'une copie : = T3 , , T5) */
            if (strcmp(quad[j].oper, "=") == 0 && strcmp(quad[j].op1, res) == 0)
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

/* ============================================================
 *  AFFICHAGE APRÈS OPTIMISATION (sans les NOP)
 * ============================================================ */
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

/* ============================================================
 *  FONCTION PRINCIPALE D'OPTIMISATION
 *  Applique les passes dans l'ordre recommandé par le cours :
 *  1. Propagation de copie
 *  2. Élimination des expressions redondantes
 *  3. Élimination du code mort
 *  Plusieurs passes sont faites car chaque passe peut
 *  créer de nouvelles opportunités pour la suivante.
 * ============================================================ */
void optimiser()
{
    printf("\n============================================================\n");
    printf("           OPTIMISATION DU CODE INTERMEDIAIRE\n");
    printf("============================================================\n");

    /* Passe 1 */
    propagation_copie();
    elimination_redondantes();
    elimination_code_inutile();

    /* Passe 2 : une 2e passe exploite les nouvelles copies créées */
    propagation_copie();
    elimination_redondantes();
    elimination_code_inutile();

    afficher_qdr_optimise();
}