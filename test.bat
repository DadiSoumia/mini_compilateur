@echo off
flex lexical_pro.l
bison -d syntaxique.y
gcc lex.yy.c syntaxique.tab.c ts.c quad.c optim.c asm_gen.c -I. -o tester.exe
tester.exe < test_project.txt
pause