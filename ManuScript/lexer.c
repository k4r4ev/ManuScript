#include "lexer.h"

char** lexer(char* buffer) {
	spacesRemoving(buffer);
	int tokenNumberInt = 0;
	for (int i = 0; i < strlen(buffer); i++) {
		if (buffer[i] == ';') {
			tokenNumberInt++; //������� ���������� �������
		}
	}
	if (tokenNumberInt == 0) {
		buffer[strlen(buffer)] = ';';
		tokenNumberInt++;
	}
	char** tokens; //������� ������ ��� �������
	tokens = (char**)malloc(tokenNumberInt + 1 * MAX_SIZE);
	for (int i = 0; i < tokenNumberInt + 1; i++) {
		tokens[i] = (char*)malloc(MAX_SIZE);
	}
	char* tokenNumberChar = (char*)malloc(512);
	_itoa_s(tokenNumberInt, tokenNumberChar, _countof(tokenNumberChar), 10); //���������� ������� ��� ������ � ������ �������
	memcpy(tokens[0], tokenNumberChar, sizeof(&tokenNumberChar)); //���������� ����� ������� � ������ �������
	for (int i = 1; i < tokenNumberInt + 1; i++) {
		char token[512] = { 0 };
		strncpy_s(token, sizeof(token), buffer, (strstr(buffer, ";")) - buffer + 1); //���� � ��������� ������ � token
		stringRemoving(buffer, (strstr(buffer, ";")) - buffer + 1); //������� ������ �� ������
		strncpy_s(tokens[i], sizeof(token), token, sizeof(token));
	}
	return tokens;
}

void spacesRemoving(char* buffer) {
	int i = 0, j = 0;
	bool quotes = false; //������� � �������� �� �������
	while ((buffer[i] = buffer[j++]) != '\0') {
		if (buffer[i] == '"')
			quotes = !quotes;
		if ((buffer[i] != ' ') || (quotes == true))
			i++;
	}
}

void stringRemoving(char* buffer, int j) {
	int i = 0;
	while ((buffer[i] = buffer[j++]) != '\0')
		i++;
}
