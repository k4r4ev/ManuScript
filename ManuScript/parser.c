#include "parser.h"

void parser(char* string) {
	char buffer[MAX_SIZE] = { 0 };
	double value = 0.0;
	char* variable = 0;
	char* function = 0;
	char* argument = 0;
	int i = 0, k = 0;
	for (i; (string[i] != '(') && (string[i] != '=') && (string[i] != ';') && (string[i] != '\0'); i++)
		buffer[i] = string[i]; //�������� ������� ��� ����������
	switch (string[i]) {
	case '(':
		i++;
		function = buffer; //��������� �������
		argument = brackets(string, &i);
		textFunction(function, argument);
		break;
	case '=':
		variable = buffer; //��������� �������
		while ((string[k] = string[++i]) != '\0') //������� ��� �� ����� �����
			k++;
		string[--k] = '\0'; //������� ����� � �������
		value = expression(string); //���������� ���������� ����� ����� ����� ���������
		printf("\t%s = %lf \n", variable, value); //������ ����������
		break;
	default:
		function = buffer; //��������� �������
		break;
	}
}

double expression(char* buffer) { //������� ��� ���������� ���������
	int index = 0; //������� ������� �������
	double value = element(buffer, &index); //�������� ������ �������
	for (;;)
		switch (buffer[index++]) //�������� �� ������ �������� �������
		{
		case '\0': //����� ������
			return value;
		case '+': //���� ����, ���������� ������� � value
			value += element(buffer, &index);
			break;
		case '-': //���� �����, �������� ������� �� value
			value -= element(buffer, &index);
			break;
		default: //��������� �� ����������
			continue;
		}
}

double element(char* buffer, int* index) { //������� ��� ������� ��������
	double value = function(buffer, index); //�������� ������ ����� �������� � ����������� ��������
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

double function(char* buffer, int* index) { //������� ��� ���������� �������
	int buf_index = 0;
	char* p_str; //��������� ��������� ��� ��������� ��������
	double value = 0.0;
	while (isalpha(buffer[*index])) { //���� ������
		buf_index++; //������� ����
		*index = *index + 1;
	}
	if (!buf_index) { //���� ��� �� ����� �����, �� ���������� �����
		value = number(buffer, index);
		return value;
	}
	else { //����� �������, �������� �� ����� ���-������ ����
		p_str = malloc(buf_index + 1); //� ��� ����� ������� ��������� ������, ����� ��������
		p_str[buf_index] = '\0';
		strncpy_s(p_str, sizeof(p_str), buffer + (*index - buf_index), buf_index);
		return mathFunction(p_str, number(buffer, index));	//���������� �������
	}
}

double number(char* buffer, int* index) { //�������, ������������ �����
	double value = 0.0; //������ �������������� ��������
	if (buffer[*index] == '(') {
		*index = *index + 1;
		char* p_substr = 0;
		p_substr = brackets(buffer, index);
		value = expression(p_substr);
		return value;
	}
	while (isdigit(buffer[*index])) { //���� ����������� ������� �����, ���������� ������� � �����
		char p_str = buffer[*index]; //�������� ����� ����� ��������� ������ � atof
		value = 10 * value + atof(&p_str); //������������ � double
		*index = *index + 1;
	}
	if ((buffer[*index] != '.') && (buffer[*index] != ',')) { //���� �� �����, ��������� �� ���������� �����
		return value;
	}
	double factor = 1.0; //��������� ��� ���������� ��������
	*index = *index + 1;
	while (isdigit(buffer[*index])) { //��������� ����, ���� ���� �����, ���������� ���������� �����
		factor *= 0.1;
		char p_str = buffer[*index]; //�������� ����� ����� ��������� ������ � atof
		value = value + atof(&p_str) * factor;
		//value = value + atof(buffer[*index]) * factor; //������ �������������� ���������
		*index = *index + 1;
	}
	return value;
}

char* brackets(char* buffer, int* index) {	//������� ��� ���������� ���������
	char buf[128];	//��������� ������������ ��� ���������
	char* p_str = (char*)malloc(MAX_SIZE);	//��������� �� ����� ������ ��� ��������
	int numL = 0;	//������� ��������� ����� ������
	int buf_index = *index;	//��������� ��������� �������� index
	do {
		buf[*index - buf_index] = buffer[*index];	//�������� ������ ������� ������ � ���������
		switch (buf[*index - buf_index]) {	//�������, �� ��� �� ������
		case ')':
			if (numL == 0) {
				buf[*index - buf_index] = '\0';	//���� ������� �������� ������, ������ ������ ����� ������
				*index = *index + 1;	//������������� ������ �� ��������� �� ��������� �������
				strncpy_s(p_str, MAX_SIZE, buf, MAX_SIZE);	//� �������� ��������� � ����� ������
				if (p_str != 0) return p_str;
			}
			else
				numL--;	//��������� ������� ������
			break;
		case '(':
			numL++;	//�������������� �����������
			break;
		}
		*index = *index + 1;
	} while (buffer[*index] != '\0');	//������������� ������ � ��������� �������
	return p_str;
}
