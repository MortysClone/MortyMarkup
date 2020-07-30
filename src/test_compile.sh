flex lex.l 
yacc -d parse.y 
gcc lex.yy.c y.tab.c node.c for_test.c html.c -o mark -g
