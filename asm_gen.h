#ifndef ASM_GEN_H
#define ASM_GEN_H

#include "quad.h"

/*
 * Génère un fichier .asm (assembleur 8086)
 * à partir des quadruplets optimisés dans quad[].
 * Le fichier généré s'appelle "output.asm".
 */
void generer_asm();

#endif