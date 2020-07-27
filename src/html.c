#include "main.h"

#define Paragraph_open "<div>"
#define Paragraph_close "</div>"

#define HeaderOne_open "<H1>"
#define HeaderOne_close "</H1>"

#define HeaderTwo_open "<H2>"
#define HeaderTwo_close "</H2>"


char* custom_strdup(char* s){
	size_t len = strlen(s) + 1; 
	char* ret = (char*)calloc(1,len);
	if(ret != NULL){
		strcpy(ret, s); 
	}
	return ret; 
}

char* custom_strndup0(char* s, size_t n){
	size_t i; 
	char* p = s;
	char* new; 
	for(i=0;i<n && *p;i++,p++); 
	
	new = (char*)malloc(i+1); 
	if(new){
		memcpy(new, s, i); 
		new[i] = '\0'; 
	}
	return new; 
}

//vincible과 victim을 더해서 새로운 할당
char* string_add(char* vincible, char* victim){
	char* html_string = NULL; 
	
	if(victim == NULL){
		return NULL;
	}

	if(vincible == NULL){
		html_string = custom_strdup(victim); 
		free(victim); 	
	} else {
		/* 1 is NULL space and 2 is "\n\n"*/
		html_string = (char*)malloc(strlen(vincible) + strlen(victim) + 1 + 1); 
		sprintf(html_string, "%s\n%s", vincible, victim);
		free(vincible); 
		free(victim); 
	}
	return html_string; 
}

char* make_html(parser_state* p){
	//printf("Make Html!\n"); 
	char* html_string = NULL; //전체적인 html문자열을 담을 포인터 
	Node* paragraph = p->lval->next_node; 
	char* pcontent_html = NULL; //html tag + lit_string 
	while(paragraph != NULL){
		char* open_paragraph_html = custom_strdup(Paragraph_open);
		html_string = string_add(html_string, open_paragraph_html); //완성된 html
		Node* pcontent = paragraph->property->next_node; 

		while(pcontent != NULL){
			size_t str_len = pcontent->property->value.string->len;  //pcontent list_string length
			char* pcontent_str = pcontent->property->value.string->str; //pcontent list_string 

			switch(pcontent->type){
				case NODE_HEADER_ONE:
					pcontent_html = (char*)malloc(str_len + strlen(HeaderOne_open) + strlen(HeaderOne_close) + 1); 
					sprintf(pcontent_html, "%s%s%s", HeaderOne_open, pcontent_str, HeaderOne_close);
					html_string = string_add(html_string, pcontent_html); 
					break;

				case NODE_HEADER_TWO:
					pcontent_html = (char*)malloc(str_len + strlen(HeaderTwo_open) + strlen(HeaderTwo_close) + 1); 
					sprintf(pcontent_html, "%s%s%s", HeaderTwo_open,  pcontent_str, HeaderTwo_close);
					html_string = string_add(html_string, pcontent_html); 
					break;

				default:
					break;	

			}
			pcontent = pcontent->next_node; 
		}
		char* close_paragraph_html = custom_strdup(Paragraph_close); 
		html_string = string_add(html_string, close_paragraph_html); 
		paragraph = paragraph->next_node; 
	}
	return html_string;
}

