
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

%type <node> mddoc paragraphs 
%type <node> paragraph pcontents pcontent pstring
%type <node> ptext

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
	  {
			p->lval = $1;
	  }
	  ;

paragraphs : /* None */
		   {
				$$ = paragraph_list_new(); 
		   }
		   | paragraph
			{
				$$ = paragraph_list_new(); 
				paragraph_list_add($$, $1); 
			}
		   | paragraphs terms paragraph
			{
				$$ = $1; 
				paragraph_list_add($1, $3); 
			}
		   ;

paragraph : keyword_paragraph op_rasgn '{' pcontents opt_terms '}'
		  {
			$$ = node_paragraph($4);
		  }
		  ;


/* pcontents에 대한 노드 리스트를 만들어야 하는가 */
pcontents : pcontent 
		  {
			/*pcontents 노드 리스트 생성 후, pcontent노드 추가 */
			$$ = pcontent_list_new(); 
			pcontent_list_add($$, $1);  
		  }
			/*pcontent에 대한 노드에 next_node로 추가해나가야함
			  $$ = $1; pcontent_node_add($1, $3); 이런느낌	.*/
		  | pcontents terms pcontent
		  {
			 $$ = $1; 
			 pcontent_list_add($1, $3); 
		  } 
		  ;

pcontent : keyword_header_one op_rasgn '{' ptext opt_terms '}'
		 {
			$$ = node_header_one($4); 
		 }
		 | keyword_header_two op_rasgn '{' ptext opt_terms '}'
		 {
			$$ = node_header_two($4); 
		 }
		 ;

/* $$는 좌변의 값 */
ptext : pstring {$$ = $1;}
	  ;

pstring : lit_string { $$ = $<node>1; } 
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
//error list 만들기 
static void yyerror(parser_state* p, const char* s){
	p->nerr++; 

	printf("line number : [%d]\nerror : %s\n",p->lineno, s);
}



