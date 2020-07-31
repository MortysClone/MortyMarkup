#include "main.h"

int main(int argc, char** argv){

	
	char* html = morty_to_html("Paragraph->{H1->{\"Hello Word?\"}}");
	printf("%s\n", html);
	free(html);
	return 0;
}
