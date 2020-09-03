#include "main.h"

extern FILE* yyin;

int main(int argc, char** argv){

	int i, n=0; 
	if(argc != 2){
		return 1; 
	}
	n = syntax_check(argv[1]); 
	if(n == 1){
		return 1; 
	}
	return 0;
}

int syntax_check(const char* fname){
	int n; 
	FILE* fp = fopen(fname, "r"); 
	if(fp == NULL){
		fprintf(stderr, "failed to open file: %s\n", fname);
		return 1; 
	}
	parser_state state = {0, fname, 1, 1, NULL}; 
	yyin = fp; 
	n = yyparse(&state); 
	if(n == 0 && state.nerr == 0){
		printf("%s Syntax OK\n", fname);
		return 0;
	} else {
		printf("%s Syntax NG\n", fname);
		return 1;
	}
	fclose(fp); 

}
