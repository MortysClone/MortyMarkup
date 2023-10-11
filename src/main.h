#ifndef _NODE_H_
#define _NODE_H_


#include <onion/onion.h>
#include <onion/log.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <onion/exportlocal.h>

#include "cJSON.h"

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
   	char* err_string; 	
} parser_state;

typedef struct result_html{
	char* value;  
	int check; 
} result_html;


typedef struct yy_buffer_state *YY_BUFFER_STATE;

//yyparse 
void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer  );
YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );
int yyparse(parser_state*);
void yyrestart(FILE* fp);
//YY_BUFFER_STATE yy_scan_string ( const char *yy_str   );
//int yy_scan_string ( const char *yy_str   );

//make lit_string to malloc 
Node* node_string_new(char* str, size_t len);

//make header one node 
Node* node_header_one(Node* property_node); 
Node* node_header_two(Node* property_node); 

Node* node_paragraph(Node* property_node);

//return error;
void print_error(unsigned int err_number);

//call yyparse, yyrestart 
int node_parse(const char* input, parser_state* p);

//dump node for test 
void node_dump(parser_state* p); 

//node free~ 
void node_free(parser_state* p);

//MortyMarkup to HTML
result_html* morty_to_html(const char* input);

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


//when server shutdown 
void shutdown_server(int _);

//return server url list 
onion_url* init_url(); 

//view 
int index_view(void* p, onion_request* req, onion_response* res);
int docs_view(void* p, onion_request* req, onion_response* res);
int community_view(void* p, onion_request* req, onion_response* res);
int write_view(void* p, onion_request* req, onion_response* res);
int read_view(void* p, onion_request* req, onion_response* res);
int delete_view(void* p, onion_request* req, onion_response* res);
int translate_view(void* p, onion_request* req, onion_response* res);
int docs_detail_view(void* p, onion_request* req, onion_response* res); 

cJSON* make_json(int err, char* value);

#endif


