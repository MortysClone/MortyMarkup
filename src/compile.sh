flex lex.l 
yacc -d parse.y 
gcc lex.yy.c y.tab.c node.c main.c -o mark
