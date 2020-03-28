#include "lexer.h"

char** lexer(char* buffer) {
	spacesRemoving(buffer);
	return prepareTokens(buffer);
}

void spacesRemoving(char* buffer) {
	int i = 0, j = 0;
	bool quotes = false; //пробелы в кавычках не удаляем
	while ((buffer[i] = buffer[j++]) != '\0') {
		if (buffer[i] == '"')
			quotes = !quotes;
		if ((buffer[i] != ' ') || (quotes == true))
			i++;
	}
}

char** prepareTokens(char* buffer) {
	int tokensCount_Int = 0;
	for (int i = 0; i < strlen(buffer); i++) {
		if (buffer[i] == ';') {
			tokensCount_Int++; //считаем количество токенов
		}
	}
	if (tokensCount_Int == 0) {
		buffer[strlen(buffer)] = ';';
		tokensCount_Int++;
	}
	char** tokens; //создаем массив для токенов
	tokens = (char**)malloc(tokensCount_Int + 1 * sizeof(char[MAX_SIZE]));
	for (int i = 0; i < tokensCount_Int + 1; i++) {
		tokens[i] = (char*)malloc(sizeof(char[MAX_SIZE]));
	}
	char* tokensCount_Char = (char*)malloc(sizeof(char[MAX_SIZE]));
	_itoa_s(tokensCount_Int, tokensCount_Char, _countof(tokensCount_Char), 10); //количество токенов для записи в массив токенов
	memcpy(tokens[0], tokensCount_Char, sizeof(&tokensCount_Char)); //записываем число токенов в первый элемент
	for (int i = 1; i < tokensCount_Int + 1; i++) {
		char token[MAX_SIZE];
		strncpy_s(token, sizeof(token), buffer, (strstr(buffer, ";")) - buffer + 1); //ищем и сохраняем строку в token
		deleteCurrentToken(buffer, (strstr(buffer, ";")) - buffer + 1); //удаляем строку из буфера
		strncpy_s(tokens[i], sizeof(token), token, sizeof(token));
	}
	return tokens;
}

void deleteCurrentToken(char* buffer, int j) {
	int i = 0;
	while ((buffer[i] = buffer[j++]) != '\0')
		i++;
}
