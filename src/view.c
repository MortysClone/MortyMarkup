#include "main.h"

const int True = 1;
const int False = 0; 

//call morty_to_html and require file name argument or char* string 
//string을 file pointer로 변환 가능 
int index_view(void* p, onion_request* req, onion_response* res){
	onion_response_printf(res, "%s", "Hello WOrl");
	return OCS_PROCESSED;
}

int docs_view(void* p, onion_request* req, onion_response* res){
	return OCS_PROCESSED; 
}

int community_view(void* p, onion_request* req, onion_response* res){
	return OCS_PROCESSED; 
}

int write_view(void* p, onion_request* req, onion_response* res){
	return OCS_PROCESSED; 
}

int read_view(void* p, onion_request* req, onion_response* res){
	return OCS_PROCESSED;
}

int delete_view(void* p, onion_request* req, onion_response* res){
	return OCS_PROCESSED;
}

cJSON* make_translate_json(int err, const char* value){
	cJSON* monitor = cJSON_CreateObject(); 
	if(cJSON_AddNumberToObject(monitor, "success", err) == NULL){
		cJSON_Delete(monitor); 
		return NULL; 
	} 
	if(cJSON_AddStringToObject(monitor, "value" , value) == NULL){
		cJSON_Delete(monitor); 
		return NULL; 
	}

	return monitor; 
}

int translate_view(void* p, onion_request* req, onion_response* res){

	cJSON* monitor = NULL; 
	char* cjson_string = NULL; 
	char* html = NULL; //previous free 	
	const char* req_data = NULL; //previous free 

	if(!(onion_request_get_flags(req) & OR_POST)){
		monitor = make_translate_json(False, "please use POST method");
		if(monitor == NULL) {
			return OCS_INTERNAL_ERROR; 
		}
		goto end; 
	}
	
	req_data = onion_request_get_post(req, "data"); 
	if(req_data == NULL){
		monitor = make_translate_json(False, "please input data");
		if(monitor == NULL){
			return OCS_INTERNAL_ERROR;
		}
		goto end; 
	}
	html = morty_to_html(req_data);
	//free((char*)req_data); 
	if(html == NULL){
		monitor = make_translate_json(False, "Syntax Error");
		if(monitor == NULL){
			return OCS_INTERNAL_ERROR; 
		}
		goto end; 
	} 
	else{
		monitor = make_translate_json(True, html);
		free(html); 
		if(monitor == NULL){
			return OCS_INTERNAL_ERROR; 
		}
		goto end; 
	}

end:
	cjson_string = cJSON_Print(monitor);
	if(cjson_string == NULL){
		cJSON_Delete(monitor); 
		return OCS_INTERNAL_ERROR; 
	} 
	else{
		cJSON_Delete(monitor);
		onion_response_printf(res, "%s", cjson_string);
		free(cjson_string);
		return OCS_PROCESSED; 
	}
}
























