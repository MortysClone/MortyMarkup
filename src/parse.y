
%{
#include "main.h"

static void yyerror(parser_state* p, const char *s);
//extern FILE* yyin;

#define YYDEBUG 1 
#define YYERROR_VERBOSE 1

%}

%union{
	Node* node; 
}

%pure-parser
%parse-param {parser_state* p}
%lex-param {p}
%{
int yylex(YYSTYPE *lval, parser_state* p);
%}

%token 
		lit_string 
		keyword_header_one 
		keyword_header_two
		op_rasgn 
		keyword_paragraph 
%%


mddoc : paragraphs opt_terms
	  ;

paragraphs : /* None */
		   | paragraph
		   | paragraphs terms paragraph
		   ;

paragraph : keyword_paragraph op_rasgn '{' pcontents opt_terms '}'
		  ;

pcontents : pcontent
		  | pcontents terms pcontent
		  ;

pcontent : keyword_header_one op_rasgn '{' ptext opt_terms '}'
		 | keyword_header_two op_rasgn '{' ptext opt_terms '}'
		 ;

ptext : pstring
	  ;

pstring : lit_string 
		;

opt_terms : /* None */
		 | terms
		 ; 

terms : term 
	  | terms term 
	  ;

term : '\n'
	 | ' '
	 | '\t' 
	 ;


%%

//#include "lex.yy.c"

static void yyerror(parser_state* p, const char* s){
	p->nerr++; 
	printf("line number : [%d]\nerror : %s\n",p->lineno, s);
}
