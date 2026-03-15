flex lexical_pro.l
bison -d syntaxique.y
gcc lex.yy.c -o tester
tester < test_project.txt
    