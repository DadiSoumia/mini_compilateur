#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"

#define FACTEUR_L 0.75
#define INITIAL_SIZE 15

char *Type = NULL;
TableHashage *table = NULL;
// Cette fonction transforme le nom d’un identifiant en index dans la table.
unsigned int HashageColli(const char *str, int tableSize)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash   << 5) + hash) + c; // hash = hash * 33 + c
    }

    return hash % tableSize;
}

TableHashage *createHashTable(int size)
{

    TableHashage *Tabhashage = malloc(sizeof(TableHashage));
    if (Tabhashage == NULL)
    {
        printf("Erreur d'allocation de memoire pour la table de hachage.\n");
        exit(1);
    }

    Tabhashage->taille = size;
    Tabhashage->cpt = 0;

    Tabhashage->table = malloc(sizeof(InfoSymboles *) * size);
    if (Tabhashage->table == NULL)
    {
        printf("Erreur d'allocation de memoire pour la table des symboles.\n");
        free(Tabhashage);
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        Tabhashage->table[i] = NULL;
    }

    return Tabhashage;
}

void redimensionnerTabHash(TableHashage *tableHash)
{
    int nouvelleTaille = tableHash->taille * 2;
    InfoSymboles **nouvelleTable = malloc(sizeof(InfoSymboles *) * nouvelleTaille);

    if (nouvelleTable == NULL)
    {
        printf("Erreur d'allocation de memoire lors du redimensionnement.\n");
        return;
    }

    for (int i = 0; i < nouvelleTaille; i++)
    {
        nouvelleTable[i] = NULL;
    }

    for (int i = 0; i < tableHash->taille; i++)
    {
        InfoSymboles *cour = tableHash->table[i];
        while (cour != NULL)
        {
            InfoSymboles *suivant = cour->suivant;
            unsigned int nouvelIndex = HashageColli(cour->Nom, nouvelleTaille);
            cour->suivant = nouvelleTable[nouvelIndex];
            nouvelleTable[nouvelIndex] = cour;
            cour = suivant;
        }
    }

    free(tableHash->table);
    tableHash->table = nouvelleTable;
    tableHash->taille = nouvelleTaille;
}
InfoSymboles *Rechercher(TableHashage *tableHash, const char *Nom)
{
    unsigned int index = HashageColli(Nom, tableHash->taille);
    InfoSymboles *courant = tableHash->table[index];

    while (courant != NULL)
    {
        if (strcmp(courant->Nom, Nom) == 0)
        {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}
// val to string et etat const
void InsererSymbol(TableHashage *Tabhashage, char *Nom, char *Type, char *Val, int Etat)
{
    if (Rechercher(Tabhashage, Nom) != NULL)
    {

        return; // Si le symbole existe déjà, retour sans insertion
    }
    unsigned int index = HashageColli(Nom, Tabhashage->taille);

    InfoSymboles *nouvSymbol = malloc(sizeof(InfoSymboles));
    if (nouvSymbol == NULL)
    {
        printf("Erreur d'allocation de memoire pour le symbole.\n");
        return;
    }

    strcpy(nouvSymbol->Nom, Nom);
    strcpy(nouvSymbol->Type, Type);
    strcpy(nouvSymbol->Val, Val);
    nouvSymbol->Etat = Etat;

    nouvSymbol->suivant = Tabhashage->table[index];
    Tabhashage->table[index] = nouvSymbol;

    Tabhashage->cpt++;

    if (Tabhashage->cpt > Tabhashage->taille * FACTEUR_L)
    {
        // printf("Table remplie a %.2f%%, redimensionnement...\n", (float)Tabhashage->cpt / Tabhashage->taille * 100);
        redimensionnerTabHash(Tabhashage);
    }
}

void AfficherTableHG(TableHashage *tableHash)
{
    printf("\n");
    printf("+---------+-------------------+-------------------+-------------------+-----------+\n");
    printf("|  Index  |       Nom         |       Type        |   Valeur          |  Etat     |\n");
    printf("+---------+-------------------+-------------------+-------------------+-----------+\n");

    for (int i = 0; i < tableHash->taille; i++)
    {
        InfoSymboles *cour = tableHash->table[i];

        if (cour != NULL)
        {
            printf("| %-7d |", i);
            while (cour != NULL)
            {
                printf(" %-17s | %-17s | %-17s | %-10d|\n",
                       cour->Nom, cour->Type, cour->Val, cour->Etat);
                cour = cour->suivant;
                if (cour != NULL)
                {
                    printf("|         |");
                }
            }
        }
    }

    printf("+---------+-------------------+-------------------+-------------------+-----------+\n");
}

int checkdeclaration(char *idf)
{
    return (Rechercher(table, idf) != NULL);
}

void MettreAJourSymbol(TableHashage *Tabhashage, char *Nom, char *Val, char *Type, int Etat)
{
    // Recherche le symbole dans la table
    InfoSymboles *symbol = Rechercher(Tabhashage, Nom);

    // Vérifie si le symbole existe
    if (symbol == NULL)
    {
        printf("Le symbole '%s' nexiste pas dans la table, mise a jour impossible.\n", Nom);
        exit(1);
    }

    // Met à jour les informations du symbole
    if (Type != NULL)
    {
        strcpy(symbol->Type, Type);
    }
    if (Val != NULL)
    {
        strcpy(symbol->Val, Val);
    }

    symbol->Etat = Etat;
}

void setType(char *type)
{
    Type = type;
}
