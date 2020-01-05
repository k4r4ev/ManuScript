#include "functions.h"

double mathOperation(char* function, double value, int* index, int temp_index) {
	if (strcmp(function, "sin") == 0) { //синус в градусах
		value = sin(3.141592 / 180 * value);
		*index = temp_index;
		//free(p_str); //не забываем удалить временную строку
		return value;
	}
	else if (strcmp(function, "cos") == 0) { //косинус в градусах
		value = cos(3.141592 / 180 * value);
		*index = temp_index;
		return value;
	}
	else if (strcmp(function, "tan") == 0) { //тангенс в градусах
		value = tan(3.141592 / 180 * value);
		*index = temp_index;
		return value;
	}
	else if (strcmp(function, "ctg") == 0) { //котангенс в градусах
		value = 1 / tan(3.141592 / 180 * value);
		*index = temp_index;
		return value;
	}
	else {
		return value;
	}
}
