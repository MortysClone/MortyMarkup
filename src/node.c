#include "main.h"

void morty_to_html(char* file){
	parser_state state; 
	state.nerr = 0; 
	state.lval = NULL; 
	state.lineno = 1; 
	state.tline = 1;
	node_parse(file, &state);
}


void node_parse(char* file, parser_state* p){
	FILE* fp = fopen(file, "rb");
	if(fp == NULL){
		return;
	}
	yyrestart(fp); 
	int n = yyparse(p); 
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

