#include "main.h"

result_html* morty_to_html(const char* input){
	parser_state state; 
	state.nerr = 0; 
	state.lval = NULL; 
	state.lineno = 1; 
	state.tline = 1;
	state.err_string = NULL; 
	int n = node_parse(input, &state);
	result_html* result = (result_html*)malloc(sizeof(result_html));
	if(result == NULL){
		printf("malloc error\n");
		return NULL;
	}
	if(n != 0){
		//node_dump(&state);
		node_free(&state);
		result->value = state.err_string; 
		result->check = 0; 
		return result;  
	}

	char* html = make_html(&state);
	result->value = html; 
	result->check = 1; 
	if(html == NULL){
		result->value = NULL; 
		result->check = 0; 
	}
	node_free(&state); //syntax error가 났을 때도 node free를 해줘야할듯
	return result; 
}


int node_parse(const char* input, parser_state* p){
	/*FILE* fp = fopen(file, "rb");
	if(fp == NULL){
		return 1;
	}
	*/
	//yyrestart(fp); 
	yy_switch_to_buffer(yy_scan_string(input));
	//yy_scan_string(input);
	int n = yyparse(p); 
	if(n == 0){
		//printf("Syntax OK!\n");
		return 0;
	} else {
		return 1;
	}
	//yylex_destory(); 
	//fclose(fp);
}

//넘길 때 len + 1해서 
Node* node_string_new(char* yytext, size_t len){
	
	Node* node = malloc(sizeof(Node));
	//printf("node_string_new malloc()\n");
	node->type = NODE_STRING; 
	node->property = NULL; 
	node->next_node = NULL;

	node->value.string = (MortyString*)malloc(sizeof(MortyString));
    //printf("MortyString malloc()\n");	
	node->value.string->str = custom_strndup0(yytext, len);
	//printf("string in MortyString malloc()\n");
	node->value.string->len = len; 
	return node; 
}

Node* node_paragraph(Node* property_node){
	Node* node = (Node*)malloc(sizeof(Node));
	//printf("node_paragraph malloc()\n");
	node->type = NODE_PARAGRAPH;
	node->value.string = NULL; 
	node->property = property_node;
	node->next_node = NULL; 
	return node; 
}

Node* node_header_one(Node* property_node){
	Node* node = (Node*)malloc(sizeof(Node));	
	//printf("node_header_one malloc()\n");
	node->type = NODE_HEADER_ONE; 
	node->value.string = NULL; 
	node->property = property_node; 
	node->next_node = NULL; 
	return node; 
}

Node* node_header_two(Node* property_node){
	Node* node = (Node*)malloc(sizeof(Node)); 
	//printf("node_header_two malloc()\n");
	node->type = NODE_HEADER_TWO; 
	node->value.string = NULL; 
	node->property = property_node;
	node->next_node = NULL; 
	return node; 
}

Node* pcontent_list_new(void){
	Node* node = (Node*)malloc(sizeof(Node)); 
	//printf("node_pcontent_list malloc()\n");
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
	//printf("node_paragraph_list malloc()\n");
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

void node_free(parser_state* p){
	//printf("node free start!\n");
	Node* paragraph = p->lval; 
	while(paragraph != NULL){
		Node* pcontent = paragraph->property; 
		while(pcontent != NULL){
			if(pcontent->property != NULL){
				//string object free; 
				//printf("String Object free~\n\n");
				free(pcontent->property->value.string->str); 
				free(pcontent->property->value.string); 
			}
			free(pcontent->property);
			//printf("pcontent object free~\n\n");
			Node* temp = pcontent; 
			pcontent = pcontent->next_node; 
			free(temp);
			//pcontent = pcontent->next_node; 
		}
		//printf("paragraph object free~\n\n");
		Node* temp = paragraph; 
		paragraph = paragraph->next_node; 
		free(temp); 
		//paragraph = paragraph->next_node; 
	}
}


void node_dump(parser_state* p){
	printf("node dump start!\n");
	
	//p->lval->next_node 인 이유는 pcontent와 paragraph의 첫 번째노드는 헤더 노드이다.
	if(p->lval == NULL){
		return;
	}
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












