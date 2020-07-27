#include "main.h"

//call morty_to_html and require file name argument or char* string 
//string을 file pointer로 변환 가능 
int index_view(void* p, onion_request* req, onion_response* res){
	char* filename = "test2.md"; 
	char* html = morty_to_html(filename);

	onion_response_printf(res, "%s", html);
	free(html); 
	return OCS_PROCESSED;
}
