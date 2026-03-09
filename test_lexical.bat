flex lexical_pro.l
gcc lex.yy.c -o tester
tester < test_project.txt
    