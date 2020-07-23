#include "main.h"

void morty_to_html(char* file){
	node_parse(file);
}

void node_parse(char* file){
	FILE* fp = fopen(file, "rb");
	if(fp == NULL){
		return;
	}
	yyrestart(fp); 
	int n = yyparse(); 
	if(n == 0){
		printf("Syntax OK!\n");
	} else {
		printf("Syntax NG!\n");
	}
}

//넘길 때 len + 1해서 
Node* node_string_new(char* yytext, size_t len){
	
	Node* node = malloc(sizeof(Node));
	node->type = NODE_STRING; 
	node->property = NULL; 
	node->next_node = NULL;

	node->value.string = (MortyString*)malloc(sizeof(MortyString)); 
	node->value.string->str = strndup(yytext, len);
	node->value.string->len = len; 
	return node; 
}

