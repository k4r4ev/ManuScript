#include "functions.h"

void textFunction(char* function, char* args) {
	if (strcmp(function, "print") == 0) {
		printf("\t%s\n", args);
		return;
	}
	else if (strcmp(function, "clear") == 0) {
		system("cls");
		return;
	}
	else if (strcmp(function, "info") == 0) {
		printf("\tinfo\t-\tinformation about functions\n");
		printf("\tprint\t-\toutput function\n");
		printf("\tclear\t-\tclear console\n");
		printf("\tsin\t-\tsine of the function\n");
		printf("\tcos\t-\tcosine of the function\n");
		printf("\ttan\t-\ttangent of the function\n");
		printf("\tctg\t-\tcotangent of the function\n");
		return;
	}
	else {
		printf("\ttextFunction parser error\n");
		return;
	}
}

double mathFunction(char* function, double value) {
	if (strcmp(function, "sin") == 0) { //синус в градусах
		value = sin(PI / 180 * value);
		return value;
	}
	else if (strcmp(function, "cos") == 0) { //косинус в градусах
		value = cos(PI / 180 * value);
		return value;
	}
	else if (strcmp(function, "tan") == 0) { //тангенс в градусах
		value = tan(PI / 180 * value);
		return value;
	}
	else if (strcmp(function, "ctg") == 0) { //котангенс в градусах
		value = 1 / tan(PI / 180 * value);
		return value;
	}
	else {
		printf("\tmathFunction parser error\n");
		return value;
	}
}

double varsFunction(struct variable** varsLinkedListHead, char* function, char* args) {
	if (strcmp(function, "var") == 0) { //вернуть переменную
		return getValueByVarName(varsLinkedListHead, args);
	}
	else {
		printf("\tvarsFunction parser error\n");
		return 0.0;
	}
}
