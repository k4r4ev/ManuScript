#include "lexer.h"
#include "variables.h"
#include "parser.h"

int main() {
	char** tokens = 0; //��������� ������ ��� �������� �������
	struct variable* varsLinkedListHead = NULL; //������� ������ ��� �������� ����������
	char buffer[MAX_SIZE] = { 0 };

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
