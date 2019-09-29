#include "lexer.h"

char** lexer(char* buffer) {
	spaces(buffer);
	int tokenNumberInt = 0;
	for (int i = 0; i < strlen(buffer); i++)
		if (buffer[i] == ';')
			tokenNumberInt++;		//считаем количество токенов
	char** tokens;		//создаем массив дл€ токенов
	tokens = (char**)malloc(tokenNumberInt + 1 * MAX_SIZE);
	for (int i = 0; i < tokenNumberInt + 1; i++) {
		tokens[i] = (char*)malloc(MAX_SIZE);
	}
	char* tokenNumberChar = convertToChar(tokenNumberInt);		//количество токенов дл€ записи в массив токенов
	memcpy(tokens[0], tokenNumberChar, sizeof(&tokenNumberChar));	//записываем число токенов в первый элемент
	for (int i = 1; i < tokenNumberInt + 1; i++) {
		char token[512] = { 0 };
		strncpy_s(token, sizeof(token), buffer, (strstr(buffer, ";")) - buffer + 1);    //ищем и сохран€ем строку в token
		squeeze(buffer, (strstr(buffer, ";")) - buffer + 1);    //удал€ем строку из буфера
		strncpy_s(tokens[i], sizeof(token), token, sizeof(token));
	}
	return tokens;
}

char* convertToChar(int tokenNumberInt) {
	char * tokenNumberChar = (char*)malloc(512);
	int v = 0; //количество цифр в числе
	while (tokenNumberInt > 9)
	{
		tokenNumberChar[v++] = (tokenNumberInt % 10) + '0';
		tokenNumberInt = tokenNumberInt / 10;
	}
	tokenNumberChar[v++] = tokenNumberInt + '0';
	tokenNumberChar[v] = '\0';
	char t;
	//инвертируем массив символов
	for (int i = 0; i < v / 2; i++)
	{
		t = tokenNumberChar[i];
		tokenNumberChar[i] = tokenNumberChar[v - 1 - i];
		tokenNumberChar[v - 1 - i] = t;
	}
	return tokenNumberChar;
}

void spaces(char* buffer) {
	int i = 0, j = 0;
	bool quotes = false;    //пробелы в кавычках не удал€ем
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