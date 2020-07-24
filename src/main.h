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

typedef struct parser_state{
	int nerr; 
	void *lval; 
	const char* fname; 
	int lineno; 
	int tline; 
} parser_state;

//yyparse 
int yyparse(parser_state*);
void yyrestart(FILE* fp);

//make lit_string to malloc 
Node* node_string_new(char* str, size_t len);

//return error;
void print_error(unsigned int err_number);

//call yyparse, yyrestart 
void node_parse(char* file, parser_state* p);

//dump node for test 
void node_dump(); 

//MortyMarkup to HTML
void morty_to_html(char* file);

#endif 
