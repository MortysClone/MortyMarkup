# MortyMarkup grammar
새로운 형식의 마크업 문법을 정의하고 이를 웹서버형태로 띄웁니다. 
그리고 요청된 마크업 문법을 HTML코드로 변환합니다. 

# Dependency
- Onion Web Framework

# Install
```
git clone https://github.com/kissesy/tumarkdown.git
sudo apt install flex 
sudo apt install bison
cd tumarkdown
./compile.sh
`````
## Usage
```
./a.out
```

# Main Logic
```C
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
```
새로운 마크업에 대해 문법을 정의합니다.

```C

```

```C
int translate_view(void* p, onion_request* req, onion_response* res){
	req_data = onion_request_get_post(req, "data"); 

	result = morty_to_html(req_data);
	if(result == NULL){
		return OCS_INTERNAL_ERROR; 
	}
	
	monitor = make_json(result->check, result->value); 
	free(result->value); 
	free(result);
	if(monitor == NULL){ 
		return OCS_INTERNAL_ERROR; 
	}
	goto end; 
	
end:
	cjson_string = cJSON_Print(monitor);

	else{
		cJSON_Delete(monitor);
		onion_response_printf(res, "%s", cjson_string);
		free(cjson_string);
		return OCS_PROCESSED; 
	}
}
```
사용자의 요청값을 HTML코드로 변환하여 응답해주는 코드입니다.

```C
char* make_html(parser_state* p){
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
```
만들어진 AST를 기반으로 순회하면서 HTML 코드를 생성합니다.


## Grammar 

In my grammar there are several paragraphs under mddoc. 
And you can put content in each paragraph.

H1 is Header One
H2 is Header Two 

Currently only headers from Markdown are available.
I plan to make several grammar points later.
and I will make tumarkdown to html! 
`````
Paragraph->{
	H1->{"Hello WOrld"}
}
Paragraph->{
	H2->{"Hello WOrld"}
}
`````