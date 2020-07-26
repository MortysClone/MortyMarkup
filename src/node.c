#include "main.h"

void morty_to_html(char* file){
	parser_state state; 
	state.nerr = 0; 
	state.lval = NULL; 
	state.lineno = 1; 
	state.tline = 1;
	node_parse(file, &state);

	node_dump(&state);
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

Node* node_paragraph(Node* property_node){
	Node* node = (Node*)malloc(sizeof(Node));
	node->type = NODE_PARAGRAPH;
	node->value.string = NULL; 
	node->property = property_node;
	node->next_node = NULL; 
	return node; 
}

Node* node_header_one(Node* property_node){
	Node* node = (Node*)malloc(sizeof(Node));	
	node->type = NODE_HEADER_ONE; 
	node->value.string = NULL; 
	node->property = property_node; 
	node->next_node = NULL; 
	return node; 
}

Node* node_header_two(Node* property_node){
	Node* node = (Node*)malloc(sizeof(Node)); 
	node->type = NODE_HEADER_TWO; 
	node->value.string = NULL; 
	node->property = property_node;
	node->next_node = NULL; 
	return node; 
}

Node* pcontent_list_new(void){
	Node* node = (Node*)malloc(sizeof(Node)); 
	node->type = NODE_PCONTENT_LIST; 
	node->value.string = NULL; 
	node->property = NULL; 
	node->next_node = NULL;  //여기에 pcontent들을 연결 
	return node; 
}

void pcontent_list_add(Node* vincible, Node* victim){
	Node* curr = vincible; 
	while(curr->next_node != NULL){
		curr = curr->next_node; 
	}
	curr->next_node = victim; 
}


Node* paragraph_list_new(void){
	Node* node = (Node*)malloc(sizeof(Node)); 
	node->type = NODE_PARAGRAPH_LIST;
	node->value.string = NULL; 
	node->property = NULL; 
	node->next_node = NULL; 
	return node; 
}

void paragraph_list_add(Node* vincible, Node* victim){
	Node* curr = vincible; 
	while(curr->next_node != NULL){
		curr = curr->next_node; 
	}
	curr->next_node = victim; 
}


void node_dump(parser_state* p){
	printf("node dump start!\n");
	
	//p->lval->next_node 인 이유는 pcontent와 paragraph의 첫 번째노드는 헤더 노드이다.
	Node* paragraph = p->lval->next_node; 
	while(paragraph != NULL){
		Node* pcontent = paragraph->property->next_node;  
		printf("[Paragraph]\n");
		while(pcontent != NULL){
			switch(pcontent->type){
				case NODE_HEADER_ONE:
					printf("HEADER_ONE : %s\n",pcontent->property->value.string->str);
					break; 
				case NODE_HEADER_TWO:
					printf("HEADER_TWO : %s\n", pcontent->property->value.string->str);
					break; 
			}
			pcontent = pcontent->next_node; 
		}
		paragraph = paragraph->next_node; 
	}
}












