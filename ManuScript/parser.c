#include "parser.h"

void parser(char* string, struct variable** varsLinkedListHead) {
	char buffer[MAX_SIZE] = { 0 };
	double value = 0.0;
	char* variable = 0;
	char* function = 0;
	char* argument = 0;
	int i = 0, k = 0;
	for (i; (string[i] != '(') && (string[i] != '=') && (string[i] != ';') && (string[i] != '\0'); i++) {
		buffer[i] = string[i]; //получаем функцию или переменную
	}
	switch (string[i]) {
	case '(':
		i++;
		function = buffer; //сохраняем функцию
		argument = brackets(string, &i);
		textFunction(function, argument);
		break;
	case '=':
		variable = &buffer; //сохраняем функцию
		while ((string[k] = string[++i]) != '\0') //убираем все до знака равно
			k++;
		string[--k] = '\0'; //убираем точку с запятой
		value = expression(varsLinkedListHead, string); //отправляем содержимое после знака равно считаться
		pushVariable(varsLinkedListHead, variable, value);
		printf("\t%s = %lf\n", variable, getValueByVarName(varsLinkedListHead, variable)); //печать переменной
		break;
	default:
		function = buffer; //сохраняем функцию
		break;
	}
}

double expression(struct variable** varsLinkedListHead, char* buffer) { //функция для вычисления выражения
	int index = 0; //текущая позиция символа
	double value = element(varsLinkedListHead, buffer, &index); //получаем первый элемент
	for (;;) {
		switch (buffer[index++]) //действие на основе текущего символа
		{
		case '\0': //конец строки
			return value;
		case '+': //знак плюс, прибавляем элемент к value
			value += element(varsLinkedListHead, buffer, &index);
			break;
		case '-': //знак минус, вычитаем элемент из value
			value -= element(varsLinkedListHead, buffer, &index);
			break;
		default: //остальное не котируется
			continue;
		}
	}
}

double element(struct variable** varsLinkedListHead, char* buffer, int* index) { //функция для анализа элемента
	double value = function(varsLinkedListHead, buffer, index); //получить первое число элемента и накапливаем значение
	while ((buffer[*index] == '*') || (buffer[*index] == '/')) {
		if (buffer[*index] == '*') {
			*index = *index + 1;
			value *= function(varsLinkedListHead, buffer, index);
		}
		if (buffer[*index] == '/') {
			*index = *index + 1;
			value /= function(varsLinkedListHead, buffer, index);
		}
	}
	return value;
}

double function(struct variable** varsLinkedListHead, char* buffer, int* index) { //функция для выполнения функции
	int buf_index = 0;
	char* functionName; //временный указатель для сравнения символов
	double value = 0.0;
	while (isalpha(buffer[*index])) { //если символ
		buf_index++; //сколько букв
		*index = *index + 1;
	}
	if (!buf_index) { //если нет ни одной буквы, то возвращаем число
		value = number(varsLinkedListHead, buffer, index);
		return value;
	}
	else { //иначе смотрим, являются ли буквы чем-нибудь этим
		functionName = malloc(buf_index + 1); //а для этого создаем временную строку, чтобы сравнить
		functionName[buf_index] = '\0';
		strncpy_s(functionName, sizeof(functionName), buffer + (*index - buf_index), buf_index);
		if (isalpha(buffer[*index + 1])) { //если первый элемент аргумента - символ
			char* arg;
			buf_index = 0;
			*index = *index + 1;
			while (buffer[*index] != ')') {
				buf_index++;
				*index = *index + 1;
			}
			arg = malloc(buf_index + 1);
			strncpy_s(arg, sizeof(arg), buffer + (*index - buf_index), buf_index);
			varsFunction(varsLinkedListHead, functionName, arg);
		}
		else {
			return mathFunction(functionName, number(varsLinkedListHead, buffer, index));	//выполнияем функцию
		}
	}
}

double number(struct variable** varsLinkedListHead, char* buffer, int* index) { //функция, распознающая число
	double value = 0.0; //хранит результирующее значение
	if (buffer[*index] == '(') {
		*index = *index + 1;
		char* p_substr = 0;
		p_substr = brackets(buffer, index);
		value = expression(varsLinkedListHead, p_substr);
		return value;
	}
	while (isdigit(buffer[*index])) { //цикл накапливает ведущие цифры, превращает символы в число
		char p_str = buffer[*index]; //сохраним число чтобы отправить ссылку в atof
		value = 10 * value + atof(&p_str); //конвертируем в double
		*index = *index + 1;
	}
	if ((buffer[*index] != '.') && (buffer[*index] != ',')) { //если не цифра, проверяем на десятичную точку
		return value;
	}
	double factor = 1.0; //множитель для десятичных разрядов
	*index = *index + 1;
	while (isdigit(buffer[*index])) { //выполнять цикл, пока идут цифры, возвращает десятичную часть
		factor *= 0.1;
		char p_str = buffer[*index]; //сохраним число для atof, т.к. константу нельзя модифицировать
		value = value + atof(&p_str) * factor;
		*index = *index + 1;
	}
	return value;
}

char* brackets(char* buffer, int* index) {	//функция для извлечения подстроки
	char buf[128];	//временное пространство для подстроки
	char* p_str = (char*)malloc(MAX_SIZE);	//указатель на новую строку для возврата
	int numL = 0;	//счетчик найденных левых скобок
	int buf_index = *index;	//сохранить начальное значение index
	do {
		buf[*index - buf_index] = buffer[*index];	//копируем символ текущей строки в подстроку
		switch (buf[*index - buf_index]) {	//смотрим, чо это за символ
		case ')':
			if (numL == 0) {
				buf[*index - buf_index] = '\0';	//если счетчик скобочек верный, ставим символ конца строки
				*index = *index + 1;	//устанавливаем индекс на следующий за скобочкой элемент
				strncpy_s(p_str, MAX_SIZE, buf, MAX_SIZE);	//и копируем подстроку в новую память
				if (p_str != 0) return p_str;
			}
			else
				numL--;	//уменьшаем счетчик скобок
			break;
		case '(':
			numL++;	//соответственно увеличиваем
			break;
		}
		*index = *index + 1;
	} while (buffer[*index] != '\0');	//устанавливаем индекс в следующий элемент
	return p_str;
}
