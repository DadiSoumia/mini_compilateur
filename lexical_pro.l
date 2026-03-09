%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

%x COMMENT_MULTI

lettre [a-zA-Z]
chiffre [0-9]

INTEGER {chiffre}+
FLOAT {chiffre}+"."{chiffre}+
INTEGER_signe  \([+-]{chiffre}+\)
FLOAT_signe \([+-]{chiffre}+"."{chiffre}+\)

IDF {lettre}(_?[a-zA-Z0-9])*
CST INTEGER|FLOAT|INTEGER_signe|FLOAT_signe

CHAINE \"[^\"]*\" 
WS [ \t\n]+

COMM_ligne "%%".*

%%

[ \t]+          { nb_colonne += yyleng; }
\n              { nb_ligne++; nb_colonne = 1; }
{COMM_ligne}    { nb_colonne += yyleng; }

"//*"                   { BEGIN(COMMENT_MULTI); nb_colonne += yyleng; }
<COMMENT_MULTI>"*//"    { BEGIN(INITIAL); nb_colonne += yyleng; }
<COMMENT_MULTI>\n       { nb_ligne++; nb_colonne = 1; }
<COMMENT_MULTI>.        { nb_colonne += yyleng; }

"BeginProject"  { printf("Mot-cle : BeginProject\n"); nb_colonne += yyleng; }
"EndProject"    { printf("Mot-cle : EndProject\n"); nb_colonne += yyleng; }
"Setup"         { printf("Mot-cle : Setup\n"); nb_colonne += yyleng; }
"Run"           { printf("Mot-cle : Run\n"); nb_colonne += yyleng; }

"define"        { printf("Mot-cle : define\n"); nb_colonne += yyleng; }
"const"         { printf("Mot-cle : const\n"); nb_colonne += yyleng; }
"integer"       { printf("Mot-cle (Type) : integer\n"); nb_colonne += yyleng; }
"float"         { printf("Mot-cle (Type) : float\n"); nb_colonne += yyleng; }

"if"            { printf("Mot-cle : if\n"); nb_colonne += yyleng; }
"then"          { printf("Mot-cle : then\n"); nb_colonne += yyleng; }
"else"          { printf("Mot-cle : else\n"); nb_colonne += yyleng; }
"endIf"         { printf("Mot-cle : endIf\n"); nb_colonne += yyleng; }

"loop"          { printf("Mot-cle : loop\n"); nb_colonne += yyleng; }
"while"         { printf("Mot-cle : while\n"); nb_colonne += yyleng; }
"endloop"       { printf("Mot-cle : endloop\n"); nb_colonne += yyleng; }

"for"           { printf("Mot-cle : for\n"); nb_colonne += yyleng; }
"in"            { printf("Mot-cle : in\n"); nb_colonne += yyleng; }
"to"            { printf("Mot-cle : to\n"); nb_colonne += yyleng; }
"endfor"        { printf("Mot-cle : endfor\n"); nb_colonne += yyleng; }

"out"           { printf("Mot-cle (Ecriture) : out\n"); nb_colonne += yyleng; }

"AND"           { printf("Op. Logique : AND\n"); nb_colonne += yyleng; }
"OR"            { printf("Op. Logique : OR\n"); nb_colonne += yyleng; }
"NON"           { printf("Op. Logique : NON\n"); nb_colonne += yyleng; }

"+"             { printf("Op. Arithmetique : +\n"); nb_colonne += yyleng; }
"-"             { printf("Op. Arithmetique : -\n"); nb_colonne += yyleng; }
"*"             { printf("Op. Arithmetique : *\n"); nb_colonne += yyleng; }
"/"             { printf("Op. Arithmetique : /\n"); nb_colonne += yyleng; }

">="            { printf("Op. Comparaison : >=\n"); nb_colonne += yyleng; }
"<="            { printf("Op. Comparaison : <=\n"); nb_colonne += yyleng; }
"=="            { printf("Op. Comparaison : ==\n"); nb_colonne += yyleng; }
"!="            { printf("Op. Comparaison : !=\n"); nb_colonne += yyleng; }
">"             { printf("Op. Comparaison : >\n"); nb_colonne += yyleng; }
"<"             { printf("Op. Comparaison : <\n"); nb_colonne += yyleng; }
"="             { printf("Op. Initialisation : =\n"); nb_colonne += yyleng; }
"<-"            { printf("Op. Affectation : <-\n"); nb_colonne += yyleng; }

";"             { printf("Ponctuation : ;\n"); nb_colonne += yyleng; }
":"             { printf("Ponctuation : :\n"); nb_colonne += yyleng; }
"|"             { printf("Separateur listes variables : |\n"); nb_colonne += yyleng; }
","             { printf("Virgule : ,\n"); nb_colonne += yyleng; }
"["             { printf("Crochet Ouvrant : [\n"); nb_colonne += yyleng; }
"]"             { printf("Crochet Fermant : ]\n"); nb_colonne += yyleng; }
"("             { printf("Parenthese Ouvrante : (\n"); nb_colonne += yyleng; }
")"             { printf("Parenthese Fermante : )\n"); nb_colonne += yyleng; }
"{"             { printf("Accolade Ouvrante : {\n"); nb_colonne += yyleng; }
"}"             { printf("Accolade Fermante : }\n"); nb_colonne += yyleng; }

{CHAINE}            { printf("Chaine de caracteres : %s\n", yytext); nb_colonne += yyleng; }

{INTEGER}           { printf("Constante entiere : %s\n", yytext); nb_colonne += yyleng;  }
{INTEGER_signe}     { printf("Constante entiere signee : %s\n", yytext); nb_colonne += yyleng;  }

{FLOAT}             { printf("Constante Reelle : %s\n", yytext); nb_colonne += yyleng; }
{FLOAT_signe}       { printf("Constante Reelle Signee : %s\n", yytext); nb_colonne += yyleng; }

{IDF}               { valider_idf(yytext); nb_colonne += yyleng; }

.                   { printf("Erreur Lexicale, ligne %d, colonne %d, entité : %s\n", nb_ligne, nb_colonne, yytext); nb_colonne += yyleng; }

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