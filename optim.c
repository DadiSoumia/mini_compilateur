#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"
#include "optim.h"

/* ============================================================
 *  PROTOTYPES (fonctions publiques)
 * ============================================================ */
void simplification_algebrique();
void propagation_constante();
void propagation_copie();
void elimination_redondantes();
void elimination_code_inutile();
void afficher_qdr_optimise();
void optimiser();

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

/* ============================================================
 *  CORRECTION : contient_temporaire()
 *  Vérifie si la chaîne 'chaine' contient la temporaire 'res'
 *  comme sous-chaîne (ex: "Tabint[T32]" contient "T32").
 *  On s'assure que c'est bien une occurrence isolée de la
 *  temporaire et non un préfixe d'une autre (ex: T3 != T32).
 * ============================================================ */
static int contient_temporaire(const char *chaine, const char *res)
{
    char *pos = strstr(chaine, res);
    if (pos == NULL)
        return 0;

    /* Vérifier que le caractère APRÈS la temporaire n'est pas un chiffre
       (pour éviter de confondre T3 avec T32) */
    int len = strlen(res);
    char apres = pos[len];
    if (apres >= '0' && apres <= '9')
        return 0;

    return 1;
}

/* Remplace toutes les occurrences de 'ancien' par 'nouveau'
   dans op1 et op2 des quadruplets de start à qc-1,
   en s'arrêtant dès que 'ancien' ou 'nouveau' est réassigné (res). */
static void remplacer_dans_operandes(int start, const char *ancien, const char *nouveau)
{
    /* On ne propage pas si 'ancien' est une variable utilisateur */
    /* car elle peut etre lue directement dans output, input, etc. */
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
 *  UTILITAIRE : est_constante()
 *  Retourne 1 si la chaîne représente une constante numérique
 *  (entière ou flottante, éventuellement négative).
 * ============================================================ */
static int est_constante(const char *s)
{
    if (s == NULL || strlen(s) == 0)
        return 0;
    int i = 0;
    if (s[i] == '-')
        i++; /* signe optionnel */
    if (s[i] == '\0')
        return 0;
    int a_chiffre = 0;
    while (s[i] >= '0' && s[i] <= '9')
    {
        a_chiffre = 1;
        i++;
    }
    if (s[i] == '.')
    { /* partie décimale optionnelle */
        i++;
        while (s[i] >= '0' && s[i] <= '9')
            i++;
    }
    return (a_chiffre && s[i] == '\0');
}

/* ============================================================
 *  4. SIMPLIFICATION ALGÉBRIQUE
 *  Applique les identités algébriques classiques sur les
 *  quadruplets arithmétiques pour simplifier ou éliminer
 *  des calculs inutiles :
 *
 *  Addition :
 *    x + 0  →  (= , x , , res)
 *    0 + x  →  (= , x , , res)
 *
 *  Soustraction :
 *    x - 0  →  (= , x , , res)
 *    x - x  →  (= , 0 , , res)
 *
 *  Multiplication :
 *    x * 1  →  (= , x , , res)
 *    1 * x  →  (= , x , , res)
 *    x * 0  →  (= , 0 , , res)
 *    0 * x  →  (= , 0 , , res)
 *
 *  Division :
 *    x / 1  →  (= , x , , res)
 *    0 / x  →  (= , 0 , , res)  (x ≠ 0)
 * ============================================================ */
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

        /* ---- ADDITION ---- */
        if (strcmp(op, "+") == 0)
        {
            /* x + 0  →  = , x */
            if (est_constante(op2) && atof(op2) == 0.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }
            /* 0 + x  →  = , x */
            else if (est_constante(op1) && atof(op1) == 0.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, op2);
                strcpy(quad[i].op2, "");
            }
        }

        /* ---- SOUSTRACTION ---- */
        else if (strcmp(op, "-") == 0)
        {
            /* x - 0  →  = , x */
            if (est_constante(op2) && atof(op2) == 0.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }
            /* x - x  →  = , 0 */
            else if (strcmp(op1, op2) == 0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, "0");
                strcpy(quad[i].op2, "");
            }
        }

        /* ---- MULTIPLICATION ---- */
        else if (strcmp(op, "*") == 0)
        {
            /* x * 0  ou  0 * x  →  = , 0 */
            if ((est_constante(op1) && atof(op1) == 0.0) ||
                (est_constante(op2) && atof(op2) == 0.0))
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, "0");
                strcpy(quad[i].op2, "");
            }
            /* x * 1  →  = , x */
            else if (est_constante(op2) && atof(op2) == 1.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }
            /* 1 * x  →  = , x */
            else if (est_constante(op1) && atof(op1) == 1.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, op2);
                strcpy(quad[i].op2, "");
            }
        }

        /* ---- DIVISION ---- */
        else if (strcmp(op, "/") == 0)
        {
            /* x / 1  →  = , x */
            if (est_constante(op2) && atof(op2) == 1.0)
            {
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op2, "");
            }
            /* 0 / x  →  = , 0  (on vérifie que x != 0 pour éviter 0/0) */
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

/* ============================================================
 *  5. PROPAGATION DE CONSTANTE
 *  Si on trouve  (= , CSTE , , VAR)  où CSTE est une constante
 *  numérique, on remplace toutes les occurrences de VAR par CSTE
 *  dans les quadruplets suivants, tant que VAR n'est pas
 *  réassignée.
 *
 *  Exemple :
 *    ( = , 10 ,  , x )          →  x est lié à 10
 *    ( + , x  , y , T0 )        →  ( + , 10 , y , T0 )
 *    ( = , T0 ,  , somme )      →  inchangé (T0 n'est pas x)
 *
 *  Différence avec propagation_copie() :
 *    - propagation_copie  : propage uniquement les TEMPORAIRES
 *      (T0, T1, ...) vers leurs usages.
 *    - propagation_constante : propage les CONSTANTES NUMÉRIQUES
 *      (littéraux comme 10, 3.14, 0 ...) stockées dans n'importe
 *      quelle variable (utilisateur ou temporaire).
 *
 *  Précaution : on ne propage PAS dans les quadruplets input/output
 *  ni dans les cibles de branchement (op1 d'un BR, BZ, BNZ, BG...).
 * ============================================================ */
void propagation_constante()
{
    for (int i = 0; i < qc; i++)
    {
        if (!est_actif(i))
            continue;

        /* On cherche les affectations simples  (= , CSTE , , VAR) */
        if (strcmp(quad[i].oper, "=") != 0)
            continue;
        if (strcmp(quad[i].op2, "") != 0)
            continue;

        const char *cste = quad[i].op1; /* la constante numérique  */
        const char *var = quad[i].res;  /* la variable cible        */

        /* La source doit être une constante numérique */
        if (!est_constante(cste))
            continue;

        /* La cible ne doit pas être vide */
        if (strlen(var) == 0)
            continue;

        /* Propager dans les quadruplets suivants */
        for (int j = i + 1; j < qc; j++)
        {
            if (!est_actif(j))
                continue;

            /* Si VAR est réassignée, on arrête la propagation */
            if (strcmp(quad[j].res, var) == 0)
                break;

            /* Ne pas toucher op1 des branchements (c'est une étiquette) */
            int j_est_branchement = est_branchement(quad[j].oper);

            /* Remplacer VAR par CSTE dans op1 (sauf branchement) */
            if (!j_est_branchement && strcmp(quad[j].op1, var) == 0)
                strcpy(quad[j].op1, cste);

            /* Remplacer VAR par CSTE dans op2 */
            if (strcmp(quad[j].op2, var) == 0)
                strcpy(quad[j].op2, cste);
        }
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

            /* On ne propage que si la SOURCE est une temporaire */
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
 *   - est une temporaire (commence par T + chiffre)
 *   - n'apparaît jamais dans op1, op2, ou res d'un autre quadruplet
 *     (y compris à l'intérieur d'une chaîne comme "Tabint[T32]")
 *  On le marque NOP.
 *
 *  CORRECTION : utilisation de contient_temporaire() au lieu de
 *  strcmp() pour détecter les temporaires cachées dans les chaînes
 *  de type "Tabint[T32]" ou "Tabfloat[T37]".
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

            /* CORRECTION : on cherche la temporaire dans op1, op2 ET res
               avec contient_temporaire() pour détecter les cas cachés
               comme "Tabint[T32]" ou "Tabfloat[T37]"                    */
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
 *  Applique les passes dans l'ordre recommandé :
 *  1. Simplification algébrique  (x+0, x*1, x*0, x-x ...)
 *  2. Propagation de constante   (= , 10 , , x) → remplace x par 10
 *  3. Propagation de copie       (= , Ti , , Tj) → remplace Tj par Ti
 *  4. Élimination des expressions redondantes
 *  5. Élimination du code mort
 *  Deux passes complètes sont effectuées car chaque passe peut
 *  créer de nouvelles opportunités pour la suivante.
 * ============================================================ */
void optimiser()
{
    printf("\n============================================================\n");
    printf("           OPTIMISATION DU CODE INTERMEDIAIRE\n");
    printf("============================================================\n");

    /* Passe 1 */
    simplification_algebrique();
    propagation_constante();
    propagation_copie();
    elimination_redondantes();
    elimination_code_inutile();

    /* Passe 2 : exploite les nouvelles opportunités créées par la passe 1 */
    simplification_algebrique();
    propagation_constante();
    propagation_copie();
    elimination_redondantes();
    elimination_code_inutile();

    afficher_qdr_optimise();
}