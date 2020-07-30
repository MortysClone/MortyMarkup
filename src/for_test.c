#include "main.h"

int main(int argc, char** argv){
	if(argc != 2) return 1; 
	
	char* html = morty_to_html(argv[1]);
	printf("%s\n", html);
	free(html);
	return 0;
}
