flex lex.l 
yacc -d parse.y 
gcc cJSON.c lex.yy.c y.tab.c node.c main.c html.c view.c -lonion_static -lpthread -lrt -g
