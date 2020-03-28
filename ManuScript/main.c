#include "lexer.h"
#include "parser.h"

int main() {
	char** tokens = 0;
	char buffer[MAX_SIZE] = { 0 };
	while (gets_s(buffer, MAX_SIZE)) {
		if (strlen(buffer) == 0) break;
		tokens = lexer(buffer);
		int tokensCount = atoi(tokens[0]);
		for (int i = 1; i <= tokensCount; i++) {
			parser(tokens[i]);
		}
	}
	return 0;
}
