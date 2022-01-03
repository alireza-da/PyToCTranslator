Test.out : lex.yy.c y.tab.c y.tab.h 
	gcc lex.yy.c y.tab.c -g -ll -o Test.out

y.tab.c : translator.y
	yacc -dv translator.y

lex.yy.c : lex.l
	lex lex.l

clean :
	rm lex.yy.c y.tab.c y.tab.h Test.out
