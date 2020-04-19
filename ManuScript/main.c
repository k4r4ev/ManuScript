#include "lexer.h"
#include "parser.h"

struct variable {
	int index;
	char name[MAX_SIZE];
	double value;
};

void newVariable(struct variable* var, char* name) {
	strcpy_s(var->name, sizeof(var->name), name);
	var->index = var->index++;
}

int main() {
	char** tokens = 0;
	struct variable variables[MAX_SIZE] = {1, "tyhtyh", 55.5, 2, "jutjy", 8.5};
	for (struct variable* var = variables; var < variables + 2; var++)
	{
		printf("%lf\n", var->value);
	}
	struct variable vars;
	vars.index = 1;
	char name[MAX_SIZE] = "greg";
	newVariable(&vars, &name);
	printf("%d\n%s", vars.index, vars.name);
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
