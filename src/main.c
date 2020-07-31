#include "main.h"

//lib로 만들경우 input : string, return : html_string 일단은 파일을 input으로 하자 

onion* server = NULL; 

int main(int argc, char** argv){
	/*if(argc != 2) return 1;

	morty_to_html(argv[1]);
	*/
	signal(SIGINT, shutdown_server); 
	signal(SIGTERM, shutdown_server);

	server = onion_new(O_POOL); 
	onion_url* url = init_url(); 

	onion_listen(server);
	onion_free(server);

	return 0;
}

onion_url* init_url(){
	onion_set_hostname(server, "0.0.0.0");
	onion_url* urls = onion_root_url(server);

	onion_url_add(urls, "", index_view);
    onion_url_add(urls, "docs", docs_view);
	onion_url_add(urls, "community", community_view);
	onion_url_add(urls, "write", write_view);
	onion_url_add(urls, "read", read_view); 
	onion_url_add(urls, "delete", delete_view); 	
	
	//Markup to html code api
	onion_url_add(urls, "translate", translate_view);
	return urls;
}

void shutdown_server(int _){
	if(server){
		onion_listen_stop(server);
	    onion_free(server);	
	}
}

