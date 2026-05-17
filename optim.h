#ifndef OPTIM_H
#define OPTIM_H

#include "quad.h"

/*
 * Fonction principale : applique toutes les optimisations
 * sur le tableau global quad[] (défini dans quad.c).
 * Appeler après afficher_qdr() pour voir avant/après.
 */
void optimiser();

/* 1. Propagation de copie */
void propagation_copie();

/* 2. Élimination des expressions redondantes */
void elimination_redondantes();

/* 3. Élimination du code mort (résultat jamais utilisé) */
void elimination_code_inutile();

/* Affiche les quadruplets en sautant les NOP */
void afficher_qdr_optimise();

#endif