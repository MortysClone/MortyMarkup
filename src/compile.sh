flex lex.l 
bison -d parse.y 
gcc cJSON.c lex.yy.c parse.tab.c node.c main.c html.c view.c -lonion_static -lpthread -lrt -g
