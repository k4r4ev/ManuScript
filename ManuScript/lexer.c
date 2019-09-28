#include "lexer.h"

char** lexer(char* buffer) {
	spaces(buffer);
	//������� ���������� �������
	int tokenNumberInt = 0;
	for (int i = 0; i < strlen(buffer); i++)
		if (buffer[i] == ';')
			tokenNumberInt++;
	//������� ������ ��� �������
	char** tokens;
	tokens = (char**)malloc(512 * MAX_SIZE);
	for (int i = 0; i < 512; i++) {
		tokens[i] = (char*)malloc(512);
	}
	//���������� ������� ��� ������ � ������ �������
	char* tokenNumberChar = inverting(tokenNumberInt);
	tokenNumberChar = (char*)malloc(512);
	int v = 0; //���������� ���� � �����
	while (tokenNumberInt > 9)
	{
		tokenNumberChar[v++] = (tokenNumberInt % 10) + '0';
		tokenNumberInt = tokenNumberInt / 10;
	}
	tokenNumberChar[v++] = tokenNumberInt + '0';
	tokenNumberChar[v] = '\0';
	char t;
	//����������� ������ ��������
	for (int i = 0; i < v / 2; i++)
	{
		t = tokenNumberChar[i];
		tokenNumberChar[i] = tokenNumberChar[v - 1 - i];
		tokenNumberChar[v - 1 - i] = t;
	}
	memcpy(tokens[0], tokenNumberChar, sizeof(&tokenNumberChar));
	int i = 1;
	while (buffer[0] != '\0') {
		char token[512] = { 0 };
		strncpy_s(token, sizeof(token), buffer, (strstr(buffer, ";")) - buffer + 1);    //���� � ��������� ������ � token
		squeeze(buffer, (strstr(buffer, ";")) - buffer + 1);    //������� ������ �� ������
		//parser(token);
		//printf("%s", token);
		strncpy_s(tokens[i], sizeof(token), token, sizeof(token));
		//tokens[i] = token;
		//printf("%s", tokens[i]);
		//printf("%d", i);
		i++;
	}
	return tokens;
}

char inverting(int tokenNumberInt) {

}

void spaces(char* buffer) {
	int i = 0, j = 0;
	bool quotes = false;    //������� � �������� �� �������
	while ((buffer[i] = buffer[j++]) != '\0') {
		if (buffer[i] == '"')
			quotes = !quotes;
		if ((buffer[i] != ' ') || (quotes == true))
			i++;
	}
}

void squeeze(char* buffer, int j) {
	int i = 0;
	while ((buffer[i] = buffer[j++]) != '\0')
		i++;
}