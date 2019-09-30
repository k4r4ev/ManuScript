#include "parser.h"

void parser(char* string) {
	char buffer[128] = { 0 };
	double value = 0.0;
	char* function = 0;
	char* argument = 0;
	int i = 0, j = 0, k = 0;
	while ((string[i] != '(') && (string[i] != '=') && (string[i] != ';')) {
		buffer[j] = string[i];    //получаем команду
		i++, j++;
	}
	function = buffer;    //сохраняем функцию
	switch (string[i]) {
	case '(':
		//argument = brackets(str, ++i);
	case '=':
		while ((string[k] = string[++i]) != '\0')    //убираем все до знака равно
			k++;
		string[--k] = '\0';    //убираем точку с запятой
		value = expression(string);    //отправляем содержимое после знака равно считаться
	}
	printf("\t %s [ %s ] = %lf \n", function, argument, value);    //печать команды с аргументом
}

double expression(char* buffer) {   //функция для вычисления выражения
	int index = 0;    //текущая позиция символа
	double value = element(buffer, &index);    //получаем первый элемент
	for (;;)
		switch (buffer[index++]) //действие на основе текущего символа
		{
		case '\0':    //конец строки
			return value;
		case '+':    //знак плюс, прибавляем элемент к value
			value += element(buffer, &index);
			break;
		case '-':    //знак минус, вычитаем элемент из value
			value -= element(buffer, &index);
			break;
		default:    //остальное не котируется
			continue;
		}
}

double element(char* buffer, int* index) {  //функция для анализа элемента
	double value = function(buffer, index);    //получить первое число элемента и накапливаем значение
	while ((buffer[*index] == '*') || (buffer[*index] == '/')) {
		if (buffer[*index] == '*') {
			*index = *index + 1;
			value *= function(buffer, index);
		}
		if (buffer[*index] == '/') {
			*index = *index + 1;
			value /= function(buffer, index);
		}
	}
	return value;
}

double function(char* buffer, int* index) {  //функция для выполнения функции
	int buf_index = 0;
	int temp_index = *index; //переменная для хранения индекса (чтобы если что вернуть индекс без изменений)
	char* p_str = 0;    //временный указатель для сравнения символов
	double value = 0;
	while (isalpha(buffer[temp_index]))    //если символ
	{
		buf_index++;    //сколько букв
		temp_index++;   //текущий индекс
	}
	if (!buf_index)     //если нет ни одной буквы, то возвращаем число
	{
		value = number(buffer, index);
		return value;
	}
	else                //иначе смотрим, являются ли буквы чем-нибудь этим
	{
		p_str = malloc(buf_index + 1);  //а для этого создаем временную строку, чтобы сравнить
		p_str[buf_index] = '\0';
		strncpy_s(p_str, sizeof(p_str), buffer + *index, buf_index);
	}
	if (strcmp(p_str, "sin") == 0)      //синус в градусах
	{
		value = sin(3.141592 / 180 * number(buffer, &temp_index));
		*index = temp_index;
		free(p_str);     //не забываем удалить временную строку
		return value;
	}
	else if (strcmp(p_str, "cos") == 0) //косинус в градусах
	{
		value = cos(3.141592 / 180 * number(buffer, &temp_index));
		*index = temp_index;
		free(p_str);     //не забываем удалить временную строку
		return value;
	}
	else if (strcmp(p_str, "tan") == 0) //тангенс в градусах
	{
		value = tan(3.141592 / 180 * number(buffer, &temp_index));
		*index = temp_index;
		free(p_str);     //не забываем удалить временную строку
		return value;
	}
	else if (strcmp(p_str, "ctg") == 0) //котангенс в градусах
	{
		value = 1 / tan(3.141592 / 180 * number(buffer, &temp_index));
		*index = temp_index;
		free(p_str);     //не забываем удалить временную строку
		return value;
	}
	else
		return value;
}

double number(char* buffer, int* index) {   //функция, распознающая число
	double value = 0.0;    //хранит результирующее значение
	if (buffer[*index] == '(') {
		*index = *index + 1;
		char* p_substr = 0;
		p_substr = brackets(buffer, index);
		value = expression(p_substr);
		return value;
	}
	while (isdigit(buffer[*index])) {       //цикл накапливает ведущие цифры, превращает символы в число
		char p_str = buffer[*index];    //сохраним число чтобы отправить ссылку в atof
		value = 10 * value + atof(&p_str);    //конвертируем в double
		*index = *index + 1;
	}
	if ((buffer[*index] != '.') && (buffer[*index] != ','))    //если не цифра, проверяем на десятичную точку
		return value;
	double factor = 1.0;                //множитель для десятичных разрядов
	*index = *index + 1;
	while (isdigit(buffer[*index]))  //выполнять цикл, пока идут цифры, возвращает десятичную часть
	{
		factor *= 0.1;
		char p_str = buffer[*index];    //сохраним число чтобы отправить ссылку в atof
		value = value + atof(&p_str) * factor;
		*index = *index + 1;
	}
	return value;
}

char* brackets(const char* buffer, int* index) {  //функция для извлечения подстроки
	char buf[128];       //временное пространство для подстроки
	char* p_str = (char*)malloc(MAX_SIZE);        //указатель на новую строку для возврата
	int numL = 0;           //счетчик найденных левых скобок
	int buf_index = *index;  //сохранить начальное значение index
	do {
		buf[*index - buf_index] = buffer[*index]; //копируем символ текущей строки в подстроку
		switch (buf[*index - buf_index]) //смотрим, чо это за символ
		{
		case ')':
			if (numL == 0) {
				buf[*index - buf_index] = '\0'; //если счетчик скобочек верный, ставим символ конца строки
				*index = *index + 1;    //устанавливаем индекс на следующий за скобочкой элемент
				//p_str = (char*)malloc(MAX_SIZE);
				strncpy_s(p_str, MAX_SIZE, buf, MAX_SIZE); //и копируем подстроку в новую память
				return p_str;
			}
			else
				numL--;     //уменьшаем счетчик скобок
			break;
		case '(':
			numL++;         //соответственно увеличиваем
			break;
		}
		*index = *index + 1;
	} while (buffer[*index] != '\0');     //устанавливаем индекс в следующий элемент
	return p_str;
}