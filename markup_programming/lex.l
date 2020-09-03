%{
#include "main.h"
#include "y.tab.h" //여기에는 BISON이 각 토큰에 대해 어떻게 처리할 것인지에 대한 정보가 들어간다. 

//#define YY_DECL int yylex(YYSTYPE* yylval)

/*
 int yylex(void) : lexer을 호출하고 토큰을 리턴한다. 
 char* yytext : 매칭된 문자열의 포인터 
 yyleng : 매칭된 문자열의 길이 
 yylval : 토큰에 대한 정보 값 
 int yywrap(void) 
 FILE* yyout : 출력 파일 
 FILE* yyin : 입력파일 
 INITIAL : initial start condition 
 BEGIN : condition switch start condition 
 ECHO : 매칭된 문자열을 쓴다. 

*/
#define YY_DECL int yylex(YYSTYPE* lval, parser_state* p)

static int lex_return(parser_state* p, int c){
	p->lineno = p->tline; 
	p->tline = yylineno; 
	return c; 
}

#define LEX_RETURN(c) return lex_return(p, c)

%}

%option noyywrap
%option yylineno 

TRAIL ([\t \n]|"#"[^\n]*"\n")*
%%
"->"{TRAIL} LEX_RETURN(op_rasgn);
if LEX_RETURN(keyword_if); 
{TRAIL}elif{TRAIL} LEX_RETURN(keyword_elif); 
{TRAIL}else{TRAIL} LEX_RETURN(keyword_else); 
for LEX_RETURN(keyword_for); 
"var" LEX_RETURN(keyword_var); 

H1 LEX_RETURN(keyword_header_one); 
H2 LEX_RETURN(keyword_header_two); 
break LEX_RETURN(keyword_break); 
continue LEX_RETURN(keyword_continue); 
"+" LEX_RETURN(op_plus);
"-" LEX_RETURN(op_minus);
"/" LEX_RETURN(op_div); 
"*" LEX_RETURN(op_mul);
"=" LEX_RETURN('=');
"==" LEX_RETURN(op_eq);
"!=" LEX_RETURN(op_neq); 
"<" LEX_RETURN(op_lt); 
"<=" LEX_RETURN(op_le); 
">" LEX_RETURN(op_gt); 
">=" LEX_RETURN(op_ge);
"&&" LEX_RETURN(op_and); 
"||" LEX_RETURN(op_or); 
"&" LEX_RETURN(op_amper); 
Paragraph LEX_RETURN(keyword_paragraph); 

[(]{TRAIL} LEX_RETURN(yytext[0]); 
[)] LEX_RETURN(yytext[0]);
[}] LEX_RETURN(yytext[0]);
[{]{TRAIL} LEX_RETURN(yytext[0]);
"\n" LEX_RETURN('\n');

[A-Za-z_][A-Za-z0-9_]* {
	LEX_RETURN(keyword_ident); 
};

(([1-9][0-9]*)|0) {
	LEX_RETURN(lit_number); 
};

(([1-9][0-9]*|0)(\.[0-9][0-9]*)) {
	LEX_RETURN(lit_number); 
};

["]([^"\\\n]|\\.|\\\n)*["] { 
	//lval->node = node_string_new(yytext+1, strlen(yytext)-2); 
	LEX_RETURN(lit_string);  
};

[ \t] ;

. {
	fprintf(stderr, "lexical error %s\n", yytext);
	//return LEX_RETURN(error);
};

%%
