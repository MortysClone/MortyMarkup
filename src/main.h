#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
	NODE_HEADER_ONE, 
	NODE_HEADER_TWO,
	NODE_PARAGRAPH,
	NODE_MDDOC,
	NODE_STRING,
   	NODE_PCONTENT_LIST,
	NODE_PARAGRAPH_LIST	
} node_type; 

typedef struct _MortyString{
	char* str; 
	size_t len;
	    	
}MortyString; 


typedef struct _Node{
	node_type type; 
	union{
		MortyString* string; 
	} value;
	struct _Node* property; //header get child property like lit_string, 
	struct _Node* next_node; //header -> header and paragraph -> paragraph
}Node; 

//lval은 노드의 최상위를 의미한다. 
typedef struct parser_state{
	int nerr; 
	Node *lval; 
	const char* fname; 
	int lineno; 
	int tline; 
} parser_state;

//yyparse 
int yyparse(parser_state*);
void yyrestart(FILE* fp);

//make lit_string to malloc 
Node* node_string_new(char* str, size_t len);

//make header one node 
Node* node_header_one(Node* property_node); 
Node* node_header_two(Node* property_node); 

Node* node_paragraph(Node* property_node);

//return error;
void print_error(unsigned int err_number);

//call yyparse, yyrestart 
int node_parse(char* file, parser_state* p);

//dump node for test 
void node_dump(parser_state* p); 

//node free~ 
void node_free(parser_state* p);

//MortyMarkup to HTML
int morty_to_html(char* file);

//make html 
char* make_html(parser_state* p); 
char* custom_strdup(char* s);
char* custom_strndup0(char* s, size_t n);
char* string_add(char* vincible, char* victim); 

//pcontent list랑 Paragraph 리스트, 위 둘을 담을 p->lval

Node* pcontent_list_new(void); 
void pcontent_list_add(Node* vincible, Node* victim); 

Node* paragraph_list_new(void); 
void paragraph_list_add(Node* vincible, Node* victim); 





#endif 
