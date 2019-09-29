#include "lexer.h"
#include "parser.h"

int main() {
	char** tokens = 0;
	char buffer[MAX_SIZE] = { 0 };
	while (gets(buffer)) {
		printf("buffer - %s\n", buffer);
		tokens = lexer(buffer);
		printf("token number - %s\n", tokens[0]);
		int tokenNumber = atoi(tokens[0]);
		for (int i = 1; i <= tokenNumber; i++) {
			printf("%s\n", tokens[i]);
			parser(tokens[i]);
		}
	}
	printf("\nthe end");
	return 0;
}
