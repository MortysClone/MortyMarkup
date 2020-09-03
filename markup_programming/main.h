#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


typedef struct parser_state{
	int nerr; 
	//Node* lval; 
	const char* fname; 
	int lineno; 
	int tline; 
	char* err_string; 
}parser_state; 

typedef struct result_html{
	char* value; 
	int check; 
} result_html;

int yyparse(parser_state* ); 
void yyrestart(FILE* ); 
int syntax_check(const char* fname);
#endif 
