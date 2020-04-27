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
		printf("\tFunction parser error\n");
		return;
	}
}

double mathFunction(char* function, double value) {
	if (strcmp(function, "sin") == 0) { //����� � ��������
		value = sin(3.141592 / 180 * value);
		return value;
	}
	else if (strcmp(function, "cos") == 0) { //������� � ��������
		value = cos(3.141592 / 180 * value);
		return value;
	}
	else if (strcmp(function, "tan") == 0) { //������� � ��������
		value = tan(3.141592 / 180 * value);
		return value;
	}
	else if (strcmp(function, "ctg") == 0) { //��������� � ��������
		value = 1 / tan(3.141592 / 180 * value);
		return value;
	}
	else {
		printf("\tFunction parser error\n");
		return value;
	}
}

double argsFunction(struct variable** varsLinkedListHead, char* function, char* args) {
	if (strcmp(function, "var") == 0) { //������� ����������
		return getValueByVarName(varsLinkedListHead, args);
	}
	else {
		printf("\tFunction parser error\n");
		return 0.0;
	}
}
