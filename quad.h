#ifndef QUAD_H
#define QUAD_H

typedef struct
{
    char oper[100];
    char op1[100];
    char op2[100];
    char res[100];
} qdr;

extern qdr *quad;
extern int qc;

void quadr(char opr[], char op1[], char op2[], char res[]);
void updateQuad(int num_quad, int colon_quad, char val[]);
void afficher_qdr();
void quadL(int type, char *b, char *c, char *d);
void quadC(int type, char *b, char *c, char *d);

#endif
