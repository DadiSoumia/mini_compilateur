%{
#include <stdio.h>
#include <string.h>

int nb_ligne=1;
int nb_colonne=1;

%}

lettre [a-zA-Z]+
chiffre [0-9]+
IDF {lettre}({lettre}|{chiffre}|_)*
cst {chiffre}+


%%
"Declaration" printf("motcle\n");
"Code" printf("motcle\n");
"print" printf("motcle\n");
"IF" printf("motcle\n");
"ELSE" printf("motcle\n");
"Do" printf("motcle\n");
"END" printf("motcle\n");
"int" printf("type\n");
"flot" printf("type\n");


{IDF} printf("identificateur\n"); 
{cst} printf("constante\n"); 

"<" printf("inf\n"); 
">" printf("sup\n"); 
"==" printf("egal\n"); 
","  printf("virgule\n");
";" printf("pointverg\n");
"{" printf("acolO\n");
"}" printf("acolF\n");
":" printf("deuxpoints\n");
"*" printf("mult\n");
"+" printf("plus\n");
"-" printf("moins\n");
"/" printf("div\n");
"(" printf("parO\n");
")" printf("parF\n");
""\" printf("guillemet\n");
"<=" printf("aff\n"); 
\n {nb_ligne++; nb_colonne=1;}
[ \t] {nb_colonne++;}
. printf("inconnu\n"); 








%%

int main()
{
yylex();

return 0;
}