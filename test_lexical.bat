flex lexical_pro.l
bison -d syntaxique.y
gcc lex.yy.c syntaxique.tab.c ts.c -I. -o tester.exe
tester.exe < test_project.txt
