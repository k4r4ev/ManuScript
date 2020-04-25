#include "lexer.h"
#include "variables.h"
#include "parser.h"

int main() {
	char** tokens = 0; //двумерный массив для хранения токенов
	struct variable* varsLinkedListHead = NULL; //связный список для хранения переменных
	char buffer[MAX_SIZE] = { 0 };

	char* n = "greg";
	pushVariable(&varsLinkedListHead, n, 5.5);
	char* n1 = "gссg";
	pushVariable(&varsLinkedListHead, n1, 6.5);
	printf("%lf\n", varsLinkedListHead->value);
	printf("%lf\n", getValueByVarName(&varsLinkedListHead, n));

	while (gets_s(buffer, MAX_SIZE)) {
		if (strlen(buffer) == 0) break;
		tokens = lexer(buffer);
		int tokensCount = atoi(tokens[0]);
		for (int i = 1; i <= tokensCount; i++) {
			parser(tokens[i], &varsLinkedListHead);
		}
	}
	return 0;
}
