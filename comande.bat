flex lexical.l
gcc lex.yy.c -o tester -lfl
tester <test.txt