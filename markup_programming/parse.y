
%{
#include "main.h"
static void yyerror(parser_state* p, const char *s);


#define YYDEBUG 1 
#define YYERROR_VERBOSE 1

%}

%union{
	int test;
	//Node* node; 
}
/*
%type <node> mddoc paragraphs 
%type <node> paragraph pcontents pcontent
*/

%pure-parser
%parse-param {parser_state* p}
%lex-param {p}
%{
int yylex(YYSTYPE *lval, parser_state* p);
%}

%token 
		lit_number 
		lit_string 
		op_rasgn

%token 
		op_plus 
		op_mul
		op_minus 
		op_div

		op_neq 
		op_lt 
		op_le 
		op_gt
		op_ge 
		op_and 
		op_or 
		op_amper
		op_bar 
		op_eq 
	
%token 
		keyword_ident 
		keyword_break 
		keyword_continue 
		keyword_header_one 
		keyword_header_two 
		keyword_paragraph 
		keyword_if
		keyword_for
		keyword_var
		keyword_elif
		keyword_else 

%nonassoc op_LOWEST

%left op_amper 
%left op_bar 
%left op_or 
%left op_and 
%nonassoc op_eq op_neq 
%left op_lt op_le op_gt op_ge 
%left op_plus op_minus 
%left op_mul op_div 
%right '!' '~' 

%token op_HIGHEST

%%


mddoc : paragraphs opt_terms
	  {
			//p->lval = $1;
	  }
	  ;

paragraphs : /* None */
		   {
		   }
		   | paragraph
		   {
		   }
		   | paragraphs terms paragraph
		   {
		   }
		   ;

paragraph : keyword_paragraph op_rasgn '{' pcontents opt_terms '}'
		  {
		  }
		  ;


/* pcontents에 대한 노드 리스트를 만들어야 하는가 */
pcontents : pcontent 
		  {
		  }
		  | pcontents terms pcontent
		  {
		  } 
		  ;

pcontent : keyword_header_one op_rasgn '{' lit_string opt_terms '}'
		 {
		 }
		 | keyword_header_two op_rasgn '{' lit_string opt_terms '}'
		 {
		 }
		 /* new variable */
		 | keyword_var keyword_ident '=' expr
		 {
		 }
		 /* ordinary variable */
		 | keyword_ident '=' expr 
		 {
		 }
		 | keyword_if '(' condition ')' op_rasgn '{' pcontents opt_terms '}' opt_else
		 {
		 }
		 ; 

opt_elif : /* None */
		   | opt_elif keyword_elif '(' condition ')' op_rasgn '{' pcontents opt_terms '}'

opt_else : opt_elif 
		 | opt_elif keyword_else op_rasgn '{' pcontents opt_terms '}'
		 ;

condition : condition op_plus condition 
		  | condition op_minus condition 
		  | condition op_mul condition 
	      | condition op_div condition 
		  | condition op_bar condition 
		  | condition op_amper condition 
		  | condition op_gt condition 
		  | condition op_ge condition 
		  | condition op_lt condition 
		  | condition op_le condition 
		  | condition op_eq condition 
		  | condition op_neq condition 
		  | op_plus condition %prec '!'
		  | op_minus condition %prec '!'
		  | '!' condition 
		  | '~' condition 
		  | condition op_and condition 
		  | condition op_or condition 
		  | cond 
		  ;

cond : value 

/* + */
expr : expr op_plus expr 
	 {
					
	 	}

/* - */
	 | expr op_minus expr 
	 {

		}
/* * */
	 | expr op_mul expr
	 {

	 	}
/* / */
     | expr op_div expr 
	 {

		}
/* | */
     | expr op_bar expr 
	 {

		}

/* & */
	 | expr op_amper expr 
	 {
		
		}
/* > */
	 | expr op_gt expr 
	 {

		}
/* >= */
	 | expr op_ge expr 
	 {

		}
/* < */
	 | expr op_lt expr 
	 {

		} 
/* <= */
     | expr op_le expr 
	 {

		} 
/* == */
	 | expr op_eq expr 
	 {

		}
/* != */
	 | expr op_neq expr 
	 {

		}
/* +$2 */
	 | op_plus expr  %prec '!'
	 {

		}	
/* -$2 */
     | op_minus expr %prec '!'
	 {

		}
     | '!' expr 
	 {

		}
	 | '~' expr 
	 { 

		 }
     | expr op_and expr 
	 {

		}
	 | expr op_or expr 
	 { 

		 }
	 | '(' expr ')'
	 {

		}
	 | value 
	 ; 

value : lit_number 
	  | lit_string 
	  | keyword_ident
	  ;

/* $$ = $<node>1 */

/* $$는 좌변의 값 */
opt_terms : /* None */
		 | terms
		 ; 

terms : term 
	  | terms term 
	  ;

term : '\n'
	 ;


%%

//#include "lex.yy.c"
//error list 만들기 
/*
에러 발생시 현재 위치에 대한 context를 만들어 해당 context부터 free해나가는 상황을 만들어야함. 
*/


/*
static void yyerror(parser_state* p, const char* s){
	p->nerr++; 
	//p->err_string = custom_strdup((char*)s); 
	size_t needed = snprintf(NULL, 0, "line : [%d], %s", p->lineno, s) + 1;
    p->err_string = (char*)malloc(needed); 
    sprintf(p->err_string, "line : [%d], %s", p->lineno, s);
	//printf("line number : [%d]\nerror : %s\n",p->lineno, s);
}
*/
static void yyerror(parser_state *p, const char *s)
{
  p->nerr++;
  if (p->fname) {
    fprintf(stderr, "%s:%d:%s\n", p->fname, p->lineno, s);
  }
  else {
    fprintf(stderr, "%s\n", s);
  }
}

