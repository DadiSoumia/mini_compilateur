#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TABLEDESSYMBOLE_H
#define TABLEDESSYMBOLE_H

typedef struct InfoSymboles
{
    char Nom[20];
    char Type[20];
    char Val[50];
    int Etat;
    struct InfoSymboles *suivant;
} InfoSymboles;

typedef struct
{
    InfoSymboles **table;

    int taille;
    int cpt;
} TableHashage;

unsigned int HashageColli(const char *str, int tableSize);

TableHashage *createHashTable(int size);

void redimensionnerTabHash(TableHashage *tableHash);
InfoSymboles *Rechercher(TableHashage *tableHash, const char *Nom);
void InsererSymbol(TableHashage *Tabhashage, char *Nom, char *Type, char *Val, int Etat);
void AfficherTableHG(TableHashage *tableHash);
void supprimer(TableHashage *tableHash, char *Nom);
void MettreAJourSymbol(TableHashage *Tabhashage, char *Nom, char *Val, char *Type, int Etat);
int checkdeclaration(char *idf);
void libererTable(TableHashage *tableHash);

extern TableHashage *table;
extern int nb_ligne;
extern int column;
extern char *Type;

#endif