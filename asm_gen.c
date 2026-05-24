#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"
#include "asm_gen.h"

/* ============================================================
 * UTILITAIRE : savoir si une chaîne est une constante numérique
 * ============================================================ */
static int est_constante(const char *s)
{
    if (!s || strlen(s) == 0)
        return 0;
    int i = 0, point = 0;
    if (s[0] == '-' || s[0] == '+')
    {
        i = 1;
    }
    for (; s[i]; i++)
    {
        if (s[i] == '.' && !point)
        {
            point = 1;
            continue;
        }
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

/* ============================================================
 * UTILITAIRE : écrire une constante en tronquant la partie décimale
 * ex: "2.5" → "2", "20.0" → "20"
 * ============================================================ */
static void ecrire_constante_entiere(FILE *f, const char *op)
{
    char copie[100];
    strcpy(copie, op);
    char *point = strchr(copie, '.');
    if (point)
        *point = '\0';
    fprintf(f, "%s", copie);
}

/* ============================================================
 * UTILITAIRE : vérifier si une variable est déjà déclarée
 * ============================================================ */
static int deja_declare(char tab[][100], int nb, const char *nom)
{
    for (int j = 0; j < nb; j++)
        if (strcmp(tab[j], nom) == 0)
            return 1;
    return 0;
}

/* ============================================================
 * UTILITAIRE : stocker AX dans res (tableau ou variable)
 * ============================================================ */
static void stocker_AX(FILE *f, const char *res)
{
    char nom[100], idx[100];
    if (strchr(res, '[') && sscanf(res, "%[^[][%[^]]", nom, idx) == 2)
    {
        fprintf(f, "    MOV SI, %s\n", idx);
        fprintf(f, "    MOV %s[SI], AX\n", nom);
    }
    else
    {
        fprintf(f, "    MOV %s, AX\n", res);
    }
}

/* ============================================================
 * UTILITAIRE : charger un opérande dans AX
 * ============================================================ */
static void charger_dans_AX(FILE *f, const char *op)
{
    char nom[100], idx[100];
    if (strchr(op, '[') && sscanf(op, "%[^[][%[^]]", nom, idx) == 2)
    {
        fprintf(f, "    MOV SI, %s\n", idx);
        fprintf(f, "    MOV AX, %s[SI]\n", nom);
    }
    else if (est_constante(op))
    {
        fprintf(f, "    MOV AX, ");
        ecrire_constante_entiere(f, op);
        fprintf(f, "\n");
    }
    else
    {
        fprintf(f, "    MOV AX, %s\n", op);
    }
}

/* ============================================================
 * UTILITAIRE : charger un opérande dans BX
 * utilise DI pour ne pas écraser SI
 * ============================================================ */
static void charger_dans_BX(FILE *f, const char *op)
{
    char nom[100], idx[100];
    if (strchr(op, '[') && sscanf(op, "%[^[][%[^]]", nom, idx) == 2)
    {
        fprintf(f, "    MOV DI, %s\n", idx);
        fprintf(f, "    MOV BX, %s[DI]\n", nom);
    }
    else if (est_constante(op))
    {
        fprintf(f, "    MOV BX, ");
        ecrire_constante_entiere(f, op);
        fprintf(f, "\n");
    }
    else
    {
        fprintf(f, "    MOV BX, %s\n", op);
    }
}

/* ============================================================
 * UTILITAIRE : déclarer un temporaire utilisé comme index de tableau
 * ex: "Tabint[T32]" → déclare T32 si pas encore fait
 * ============================================================ */
static void declarer_index_tableau(FILE *f, const char *op, char temps[][100], int *nb_temps)
{
    char nom[100], idx[100];
    if (strchr(op, '[') && sscanf(op, "%[^[][%[^]]", nom, idx) == 2)
    {
        if (!est_constante(idx) && idx[0] == 'T' && idx[1] >= '0' && idx[1] <= '9')
        {
            if (!deja_declare(temps, *nb_temps, idx))
            {
                strcpy(temps[(*nb_temps)++], idx);
                fprintf(f, "    %s DW ?\n", idx);
            }
        }
    }
}

/* ============================================================
 * AFFICHAGE d'un nombre entier à l'écran via INT 21h
 * Utilise une routine de conversion en chaîne de chiffres
 * ============================================================ */
static void generer_affichage_nombre(FILE *f, const char *var, int label_id)
{
    fprintf(f, "    ; --- Afficher valeur de %s ---\n", var);
    fprintf(f, "    MOV AX, %s\n", var);
    fprintf(f, "    ; Gérer le signe négatif\n");
    fprintf(f, "    CMP AX, 0\n");
    fprintf(f, "    JGE POS_%d\n", label_id);
    fprintf(f, "    PUSH AX\n");
    fprintf(f, "    MOV DL, '-'\n");
    fprintf(f, "    MOV AH, 02h\n");
    fprintf(f, "    INT 21h\n");
    fprintf(f, "    POP AX\n");
    fprintf(f, "    NEG AX\n");
    fprintf(f, "POS_%d:\n", label_id);
    fprintf(f, "    ; Diviser par 10 et empiler les chiffres\n");
    fprintf(f, "    MOV BX, 10\n");
    fprintf(f, "    XOR CX, CX\n");
    fprintf(f, "DIV_%d:\n", label_id);
    fprintf(f, "    XOR DX, DX\n");
    fprintf(f, "    DIV BX\n");
    fprintf(f, "    PUSH DX\n");
    fprintf(f, "    INC CX\n");
    fprintf(f, "    TEST AX, AX\n");
    fprintf(f, "    JNZ DIV_%d\n", label_id);
    fprintf(f, "    ; Dépiler et afficher chaque chiffre\n");
    fprintf(f, "PRT_%d:\n", label_id);
    fprintf(f, "    POP DX\n");
    fprintf(f, "    ADD DL, '0'\n");
    fprintf(f, "    MOV AH, 02h\n");
    fprintf(f, "    INT 21h\n");
    fprintf(f, "    LOOP PRT_%d\n", label_id);
    fprintf(f, "    ; Afficher espace après le nombre\n");
    fprintf(f, "    MOV DL, ' '\n");
    fprintf(f, "    MOV AH, 02h\n");
    fprintf(f, "    INT 21h\n");
}

/* ============================================================
 * AFFICHAGE d'un message texte caractère par caractère
 * ============================================================ */
static void generer_affichage_message(FILE *f, const char *msg, int label_id)
{
    fprintf(f, "    ; --- Afficher message ---\n");
    /* Enlever les guillemets du message */
    char copie[200];
    strncpy(copie, msg, sizeof(copie) - 1);
    copie[sizeof(copie) - 1] = '\0';
    int len = strlen(copie);
    /* Enlever guillemets si présents */
    char *debut = copie;
    if (debut[0] == '"')
    {
        debut++;
        len--;
    }
    if (len > 0 && debut[len - 1] == '"')
    {
        debut[len - 1] = '\0';
        len--;
    }

    for (int i = 0; debut[i]; i++)
    {
        if (debut[i] == ' ')
            fprintf(f, "    MOV DL, ' '\n");
        else
            fprintf(f, "    MOV DL, '%c'\n", debut[i]);
        fprintf(f, "    MOV AH, 02h\n");
        fprintf(f, "    INT 21h\n");
    }
}

/* ============================================================
 * GÉNÉRATION PRINCIPALE
 * ============================================================ */
void generer_asm()
{
    FILE *f = fopen("output.asm", "w");
    if (!f)
    {
        printf("Erreur: impossible de creer output.asm\n");
        return;
    }

    /* -------- En-tête du programme 8086 -------- */
    fprintf(f, "; ============================================\n");
    fprintf(f, "; Code Assembleur 8086 genere automatiquement\n");
    fprintf(f, "; ============================================\n\n");

    fprintf(f, "PILE SEGMENT STACK\n");
    fprintf(f, "    DW 100 DUP(?)\n");
    fprintf(f, "base_pile EQU $\n");
    fprintf(f, "PILE ENDS\n\n");

    /* -------- Segment de données -------- */
    fprintf(f, "DONNEE SEGMENT\n");

    /* Déclarer Pi, Max et les tableaux en premier */
    fprintf(f, "    Pi       DW 3\n");
    fprintf(f, "    Max      DW 0\n");
    fprintf(f, "    Tabint   DW 100 DUP(?)\n");
    fprintf(f, "    Tabfloat DW 100 DUP(?)\n");

    /* Collecter les variables uniques */
    char vars[1000][100];
    int nb_vars = 0;
    strcpy(vars[nb_vars++], "Pi");
    strcpy(vars[nb_vars++], "Max");
    strcpy(vars[nb_vars++], "Tabint");
    strcpy(vars[nb_vars++], "Tabfloat");

    for (int i = 0; i < qc; i++)
    {
        if (strcmp(quad[i].oper, "NOP") == 0 || strcmp(quad[i].oper, "") == 0)
            continue;
        const char *res = quad[i].res;
        if (strlen(res) == 0)
            continue;
        if (res[0] == 'T' && res[1] >= '0' && res[1] <= '9')
            continue;
        if (strchr(res, '['))
            continue;
        if (!deja_declare(vars, nb_vars, res))
        {
            strcpy(vars[nb_vars++], res);
            fprintf(f, "    %s DW ?\n", res);
        }
    }

    /* Déclarer les temporaires */
    char temps[1000][100];
    int nb_temps = 0;
    for (int i = 0; i < qc; i++)
    {
        if (strcmp(quad[i].oper, "NOP") == 0 || strcmp(quad[i].oper, "") == 0)
            continue;
        const char *res = quad[i].res;
        if (strlen(res) == 0)
            continue;
        if (!(res[0] == 'T' && res[1] >= '0' && res[1] <= '9'))
            continue;
        if (!deja_declare(temps, nb_temps, res))
        {
            strcpy(temps[nb_temps++], res);
            fprintf(f, "    %s DW ?\n", res);
        }
    }

    /* Déclarer les temporaires utilisés comme index de tableau */
    for (int i = 0; i < qc; i++)
    {
        if (strcmp(quad[i].oper, "NOP") == 0 || strcmp(quad[i].oper, "") == 0)
            continue;
        declarer_index_tableau(f, quad[i].op1, temps, &nb_temps);
        declarer_index_tableau(f, quad[i].op2, temps, &nb_temps);
        declarer_index_tableau(f, quad[i].res, temps, &nb_temps);
    }

    fprintf(f, "DONNEE ENDS\n\n");

    /* -------- Segment de code -------- */
    fprintf(f, "LECODE SEGMENT\n");
    fprintf(f, "Debut:\n");
    fprintf(f, "    ASSUME CS:LECODE, DS:DONNEE, SS:PILE\n");
    fprintf(f, "    ; Initialisation des segments\n");
    fprintf(f, "    MOV AX, DONNEE\n");
    fprintf(f, "    MOV DS, AX\n");
    fprintf(f, "    MOV AX, PILE\n");
    fprintf(f, "    MOV SS, AX\n");
    fprintf(f, "    MOV SP, base_pile\n\n");

    /* -------- Traduction des quadruplets -------- */
    int affichage_id = 0; /* compteur unique pour les labels d'affichage */

    for (int i = 0; i < qc; i++)
    {
        if (strcmp(quad[i].oper, "NOP") == 0 || strcmp(quad[i].oper, "") == 0)
            continue;

        /* Label pour chaque quadruplet (utile pour les sauts) */
        fprintf(f, "L%d:\n", i);

        const char *op = quad[i].oper;
        const char *op1 = quad[i].op1;
        const char *op2 = quad[i].op2;
        const char *res = quad[i].res;

        /* ---- Affectation simple : (= , val , , dest) ---- */
        if (strcmp(op, "=") == 0)
        {
            charger_dans_AX(f, op1);
            stocker_AX(f, res);
        }

        /* ---- Addition : (+, op1, op2, res) ---- */
        else if (strcmp(op, "+") == 0)
        {
            charger_dans_AX(f, op1);
            if (est_constante(op2))
            {
                fprintf(f, "    ADD AX, ");
                ecrire_constante_entiere(f, op2);
                fprintf(f, "\n");
            }
            else
            {
                charger_dans_BX(f, op2);
                fprintf(f, "    ADD AX, BX\n");
            }
            stocker_AX(f, res);
        }

        /* ---- Soustraction : (-, op1, op2, res) ---- */
        else if (strcmp(op, "-") == 0)
        {
            charger_dans_AX(f, op1);
            if (est_constante(op2))
            {
                fprintf(f, "    SUB AX, ");
                ecrire_constante_entiere(f, op2);
                fprintf(f, "\n");
            }
            else
            {
                charger_dans_BX(f, op2);
                fprintf(f, "    SUB AX, BX\n");
            }
            stocker_AX(f, res);
        }

        /* ---- Multiplication : (*, op1, op2, res) ---- */
        else if (strcmp(op, "*") == 0)
        {
            charger_dans_AX(f, op1);
            charger_dans_BX(f, op2);
            fprintf(f, "    IMUL BX\n"); /* DX:AX = AX * BX */
            stocker_AX(f, res);
        }

        /* ---- Division : (/, op1, op2, res) ---- */
        else if (strcmp(op, "/") == 0)
        {
            charger_dans_AX(f, op1);
            fprintf(f, "    CWD\n"); /* étend AX dans DX:AX */
            charger_dans_BX(f, op2);
            fprintf(f, "    IDIV BX\n"); /* AX = quotient */
            stocker_AX(f, res);
        }

        /* ---- Saut inconditionnel : (BR, cible, , ) ---- */
        else if (strcmp(op, "BR") == 0)
        {
            fprintf(f, "    JMP L%s\n", op1);
        }

        /* ---- Saut si zéro : (BZ, cible, cond, ) ---- */
        else if (strcmp(op, "BZ") == 0)
        {
            charger_dans_AX(f, op2);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JE L%s\n", op1);
        }

        /* ---- Saut si non zéro : (BNZ, cible, cond, ) ---- */
        else if (strcmp(op, "BNZ") == 0)
        {
            charger_dans_AX(f, op2);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JNE L%s\n", op1);
        }

        /* ---- Saut si > 0 : (BG, cible, val, ) ---- */
        else if (strcmp(op, "BG") == 0)
        {
            charger_dans_AX(f, op1);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JG L%s\n", op1);
        }

        /* ---- Saut si >= 0 : (BGE, cible, val, ) ---- */
        else if (strcmp(op, "BGE") == 0)
        {
            charger_dans_AX(f, op1);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JGE L%s\n", op1);
        }

        /* ---- Saut si < 0 : (BL, cible, val, ) ---- */
        else if (strcmp(op, "BL") == 0)
        {
            charger_dans_AX(f, op1);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JL L%s\n", op1);
        }

        /* ---- Saut si <= 0 : (BLE, cible, val, ) ---- */
        else if (strcmp(op, "BLE") == 0)
        {
            charger_dans_AX(f, op1);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JLE L%s\n", op1);
        }

        /* ---- Output : (output, "msg", val, ) ---- */
        else if (strcmp(op, "output") == 0)
        {
            /* 1. Afficher le message texte */
            if (strlen(op1) > 0 && strcmp(op1, "") != 0)
                generer_affichage_message(f, op1, affichage_id++);

            /* 2. Afficher la valeur numérique */
            if (strlen(op2) > 0 && strcmp(op2, "") != 0)
                generer_affichage_nombre(f, op2, affichage_id++);

            /* 3. Retour à la ligne */
            fprintf(f, "    MOV DL, 0Dh\n");
            fprintf(f, "    MOV AH, 02h\n");
            fprintf(f, "    INT 21h\n");
            fprintf(f, "    MOV DL, 0Ah\n");
            fprintf(f, "    MOV AH, 02h\n");
            fprintf(f, "    INT 21h\n");
        }

        /* ---- Input : (input, var, , ) ---- */
        else if (strcmp(op, "input") == 0)
        {
            fprintf(f, "    ; --- Lire un entier depuis le clavier dans %s ---\n", op1);
            fprintf(f, "    XOR AX, AX\n"); /* AX = 0 (accumulateur) */
            fprintf(f, "    XOR BX, BX\n"); /* BX = signe (0=positif) */
            fprintf(f, "    ; Lire le premier caractère (signe ou chiffre)\n");
            fprintf(f, "    MOV AH, 01h\n");
            fprintf(f, "    INT 21h\n");
            fprintf(f, "    CMP AL, '-'\n");
            fprintf(f, "    JNE IN_DIGIT_%d\n", affichage_id);
            fprintf(f, "    MOV BX, 1\n"); /* signe négatif */
            fprintf(f, "    MOV AH, 01h\n");
            fprintf(f, "    INT 21h\n"); /* lire chiffre suivant */
            fprintf(f, "IN_DIGIT_%d:\n", affichage_id);
            fprintf(f, "    ; Accumuler les chiffres\n");
            fprintf(f, "IN_LOOP_%d:\n", affichage_id);
            fprintf(f, "    CMP AL, 0Dh\n"); /* Entrée = fin */
            fprintf(f, "    JE IN_DONE_%d\n", affichage_id);
            fprintf(f, "    SUB AL, '0'\n");
            fprintf(f, "    CBW\n");         /* AL → AX */
            fprintf(f, "    XCHG AX, CX\n"); /* sauver chiffre dans CX */
            fprintf(f, "    MOV DX, 10\n");
            fprintf(f, "    IMUL DX\n");    /* AX = AX * 10 */
            fprintf(f, "    ADD AX, CX\n"); /* AX = AX + chiffre */
            fprintf(f, "    MOV AH, 01h\n");
            fprintf(f, "    INT 21h\n"); /* lire prochain caractère */
            fprintf(f, "    JMP IN_LOOP_%d\n", affichage_id);
            fprintf(f, "IN_DONE_%d:\n", affichage_id);
            fprintf(f, "    CMP BX, 1\n");
            fprintf(f, "    JNE IN_POS_%d\n", affichage_id);
            fprintf(f, "    NEG AX\n"); /* appliquer signe négatif */
            fprintf(f, "IN_POS_%d:\n", affichage_id);
            fprintf(f, "    MOV %s, AX\n", op1);
            affichage_id++;
        }

        fprintf(f, "\n");
    }

    /* -------- Fin du programme -------- */
    fprintf(f, "L%d:\n", qc);
    fprintf(f, "    ; Fin du programme\n");
    fprintf(f, "    MOV AH, 4Ch\n");
    fprintf(f, "    INT 21h\n\n");
    fprintf(f, "LECODE ENDS\n\n");
    fprintf(f, "END Debut\n");

    fclose(f);
    printf("\n=> Fichier assembleur genere : output.asm\n");
}