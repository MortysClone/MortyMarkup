#include "main.h"

int main(int argc, char** argv){
	
	if(argc != 2){
		return 0;
	}
	FILE* fp = fopen(argv[1], "r"); 
	fseek(fp, 0, SEEK_END); 
	int size = ftell(fp); 
	char* buffer = (char*)malloc(size+1); 
	memset(buffer, 0, size+1); 
	fseek(fp, 0, SEEK_SET); 
	fread(buffer, size, 1, fp); 
	result_html* result = morty_to_html(buffer); 
	fclose(fp); 
	//char* html = morty_to_html("Paragraph->{H1->{\"Hello Word?\"}}");
	printf("%s\n", result->value);
	free(result->value);
	free(result);
	return 0;
}
