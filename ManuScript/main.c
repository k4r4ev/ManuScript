#include "lexer.h"
#include "parser.h"

int main() {
	char** tokens = 0;
	char buffer[MAX_SIZE] = { 0 };
	while (gets(buffer)) {
		if (strlen(buffer) == NULL) break;
		tokens = lexer(buffer);
		int tokenNumber = atoi(tokens[0]);
		for (int i = 1; i <= tokenNumber; i++) {
			//printf("%s\n", tokens[i]);
			parser(tokens[i]);
		}
	}
	return 0;
}
