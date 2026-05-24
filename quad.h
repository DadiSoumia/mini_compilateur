#ifndef QUAD_H
#define QUAD_H

// Declaration de la structure quadruplets
typedef struct {
    char oper[100]; 
    char op1[100];   
    char op2[100];   
    char res[100];  
} qdr;

extern qdr *quad;   /* tableau dynamique, alloue dans quad.c */
extern int qc;

// Prototypes des fonctions
void quadr(char opr[], char op1[], char op2[], char res[]);
void updateQuad(int num_quad, int colon_quad, char val[]);
void afficher_qdr();

// Fonctions pour les expressions logiques et de comparaison
void quadL(int type, char* b, char* c, char* d);
void quadC(int type, char* b, char* c, char* d);

#endif
