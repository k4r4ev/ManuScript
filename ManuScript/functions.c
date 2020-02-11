#include "functions.h"

void textFunction(char* function, char* args) {
	if (strcmp(function, "print") == 0) { //синус в градусах
		printf("\t\t%s\n", args);
		return;
	}
	else if (strcmp(function, "clear") == 0) { //косинус в градусах
		system("cls");
		return;
	}
	else {
		printf("\tFunction parser error\n");
		return;
	}
}

double mathFunction(char* function, double value) {
	if (strcmp(function, "sin") == 0) { //синус в градусах
		value = sin(3.141592 / 180 * value);
		return value;
	}
	else if (strcmp(function, "cos") == 0) { //косинус в градусах
		value = cos(3.141592 / 180 * value);
		return value;
	}
	else if (strcmp(function, "tan") == 0) { //тангенс в градусах
		value = tan(3.141592 / 180 * value);
		return value;
	}
	else if (strcmp(function, "ctg") == 0) { //котангенс в градусах
		value = 1 / tan(3.141592 / 180 * value);
		return value;
	}
	else {
		printf("\tFunction parser error\n");
		return value;
	}
}
