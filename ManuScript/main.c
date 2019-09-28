#include "lexer.h"
#include "parser.h"

int main() {
	char** tokens = 0;
	char buffer[512] = { 0 };
	while (gets(buffer)) {
		printf("buffer - %s\n", buffer);
		tokens = lexer(buffer);
		printf("buffer - %s\n", buffer);
		printf("token - %s\n", tokens[0]);
	}


	printf("\n");
	for (int a = 0; a < tokens[0]; a++)
		printf("%s\n", tokens[a]);

	printf("\nthe end");
	return 0;
}
