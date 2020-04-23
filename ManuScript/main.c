#include "lexer.h"
#include "variables.h"
#include "parser.h"

int main() {
	char** tokens = 0; // двумерный массив для хранения токенов
	struct variable* varsListHead = NULL; // связный список для хранения переменных
	char buffer[MAX_SIZE] = { 0 };

	char* n = "greg";
	pushVariable(&varsListHead, n, 5.5);
	char* n1 = "gссg";
	pushVariable(&varsListHead, n1, 6.5);
	printf("%lf\n", varsListHead->value);
	printf("%lf\n", getValueByVarName(&varsListHead, n));


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
