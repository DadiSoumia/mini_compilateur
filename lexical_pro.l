%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntaxique.tab.h"
int nb_ligne=1;
int nb_colonne=1;



void valider_idf(char* txt) {
    if (strlen(txt) > 14) {
        printf("Erreur Lexicale, ligne %d, colonne %d, Identificateur trop long : %s\n", nb_ligne, nb_colonne, txt);
    } else {
        printf("Mot detecte : Identificateur (%s)\n", txt);
    }
}

%}



lettre [a-zA-Z]
chiffre [0-9]

INTEGER {chiffre}+
FLOAT {chiffre}+"."{chiffre}+
INTEGER_signe  \([+-]{chiffre}+\)
FLOAT_signe \([+-]{chiffre}+"."{chiffre}+\)

IDF {lettre}(_?[a-zA-Z0-9])*
CST INTEGER|FLOAT|INTEGER_signe|FLOAT_signe

CHAINE \"[^\"]*\" 

COMM_ligne "%%".*
%x COMMENT_MULTI
%%

[ \t]+          { nb_colonne += yyleng; }
\n              { nb_ligne++; nb_colonne = 1; }
{COMM_ligne}    { nb_colonne += yyleng; }

"//*"                   { BEGIN(COMMENT_MULTI); nb_colonne += yyleng;  return 0; }
<COMMENT_MULTI>"*//"    { BEGIN(INITIAL); nb_colonne += yyleng; return 0; }
<COMMENT_MULTI>\n       { nb_ligne++; nb_colonne = 1; }
<COMMENT_MULTI>.        { nb_colonne += yyleng; }

"BeginProject"  { printf("Mot-cle : BeginProject\n"); nb_colonne += yyleng;  return beginProject; }
"EndProject"    { printf("Mot-cle : EndProject\n"); nb_colonne += yyleng;  return endProject; }
"Setup"         { printf("Mot-cle : Setup\n"); nb_colonne += yyleng;  return setup; }
"Run"           { printf("Mot-cle : Run\n"); nb_colonne += yyleng;  return run; }

"define"        { printf("Mot-cle : define\n"); nb_colonne += yyleng; return define; }
"const"         { printf("Mot-cle : const\n"); nb_colonne += yyleng; return const; }
"integer"       { printf("Mot-cle (Type) : integer\n"); nb_colonne += yyleng; return integer; }
"float"         { printf("Mot-cle (Type) : float\n"); nb_colonne += yyleng; return float; }

"if"            { printf("Mot-cle : if\n"); nb_colonne += yyleng; return if; }
"then"          { printf("Mot-cle : then\n"); nb_colonne += yyleng; return then; }
"else"          { printf("Mot-cle : else\n"); nb_colonne += yyleng; return else; }
"endIf"         { printf("Mot-cle : endIf\n"); nb_colonne += yyleng; return endIf; }

"loop"          { printf("Mot-cle : loop\n"); nb_colonne += yyleng; return loop; }
"while"         { printf("Mot-cle : while\n"); nb_colonne += yyleng; return while; }
"endloop"       { printf("Mot-cle : endloop\n"); nb_colonne += yyleng; return endloop; }

"for"           { printf("Mot-cle : for\n"); nb_colonne += yyleng; return for; }
"in"            { printf("Mot-cle : in\n"); nb_colonne += yyleng; return in; }
"to"            { printf("Mot-cle : to\n"); nb_colonne += yyleng; return to; }
"endfor"        { printf("Mot-cle : endfor\n"); nb_colonne += yyleng; return endfor; }

"out"           { printf("Mot-cle (Ecriture) : out\n"); nb_colonne += yyleng; return out; }

"AND"           { printf("Op. Logique : AND\n"); nb_colonne += yyleng; return AND; }
"OR"            { printf("Op. Logique : OR\n"); nb_colonne += yyleng; return OR; }
"NON"           { printf("Op. Logique : NON\n"); nb_colonne += yyleng; return NON; }

"+"             { printf("Op. Arithmetique : +\n"); nb_colonne += yyleng; return plus; }
"-"             { printf("Op. Arithmetique : -\n"); nb_colonne += yyleng; return moins; }
"*"             { printf("Op. Arithmetique : *\n"); nb_colonne += yyleng; return mult; }
"/"             { printf("Op. Arithmetique : /\n"); nb_colonne += yyleng; return Div; }

">="            { printf("Op. Comparaison : >=\n"); nb_colonne += yyleng; return sup_egal; }
"<="            { printf("Op. Comparaison : <=\n"); nb_colonne += yyleng; return inf_egal; }
"=="            { printf("Op. Comparaison : ==\n"); nb_colonne += yyleng; return egal; }
"!="            { printf("Op. Comparaison : !=\n"); nb_colonne += yyleng; return diff; }
">"             { printf("Op. Comparaison : >\n"); nb_colonne += yyleng; return sup; }
"<"             { printf("Op. Comparaison : <\n"); nb_colonne += yyleng; return inf; }
"<-"            { printf("Op. Affectation : <-\n"); nb_colonne += yyleng; return affectation; }

";"             { printf("Ponctuation : ;\n"); nb_colonne += yyleng; return pointverg; }
":"             { printf("Ponctuation : :\n"); nb_colonne += yyleng; return deuxpoint; }
"|"             { printf("Separateur listes variables : |\n"); nb_colonne += yyleng; return barre; }
","             { printf("Virgule : ,\n"); nb_colonne += yyleng; return virgule; }
"["             { printf("Crochet Ouvrant : [\n"); nb_colonne += yyleng; return crochetO; }
"]"             { printf("Crochet Fermant : ]\n"); nb_colonne += yyleng; return crochetF; }
"("             { printf("Parenthese Ouvrante : (\n"); nb_colonne += yyleng; return parO; }
")"             { printf("Parenthese Fermante : )\n"); nb_colonne += yyleng; return parF; }
"{"             { printf("Accolade Ouvrante : {\n"); nb_colonne += yyleng; return acolO; }
"}"             { printf("Accolade Fermante : }\n"); nb_colonne += yyleng; return acolF; }

{CHAINE}        { printf("Chaine de caracteres : %s\n", yytext); nb_colonne += yyleng;  return chaine; }

{INTEGER}       { printf("Constante entiere : %s\n", yytext); nb_colonne += yyleng;  return integer; }
{INTEGER_signe} { printf("Constante entiere signee : %s\n", yytext); nb_colonne += yyleng;  return integer_signe; }

{FLOAT}         { printf("Constante Reelle : %s\n", yytext); nb_colonne += yyleng; return float; }
{FLOAT_signe}   { printf("Constante Reelle Signee : %s\n", yytext); nb_colonne += yyleng; return float_signe; }

{IDF}           { valider_idf(yytext); nb_colonne += yyleng; return idf; }

.               { printf("Erreur Lexicale, ligne %d, colonne %d, entité : %s\n", nb_ligne, nb_colonne, yytext); nb_colonne += yyleng; return erreur; }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("\n Lancement Lexical \n");
    yylex();
    printf("\n Fin Lexical \n");
    return 0;
}