#include "lexer.h"

char** lexer(char* buffer) {
    spaces_removing(buffer);
    return prepare_tokens(buffer);
}

void spaces_removing(char* buffer) {
    int i = 0, j = 0;
    bool quotes = false;
    while ((buffer[i] = buffer[j++]) != '\0') {
        if (buffer[i] == '"')
            quotes = !quotes;
        if ((buffer[i] != ' ') || (quotes == true))
            i++;
    }
}

char** prepare_tokens(char* buffer) {
    int tokens_count_int = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ';') {
            tokens_count_int++;
        }
    }
    if (tokens_count_int == 0) {
        buffer[strlen(buffer)] = ';';
        tokens_count_int++;
    }
    char** tokens = (char**)malloc(tokens_count_int + 1 * sizeof(char[MAX_SIZE]));
    for (int i = 0; i < tokens_count_int + 1; i++) {
        tokens[i] = (char*)malloc(sizeof(char[MAX_SIZE]));
    }
    char* tokens_count_char = (char*)malloc(sizeof(char[MAX_SIZE]));
    _itoa_s(tokens_count_int, tokens_count_char, MAX_SIZE, 10);
    memcpy(tokens[0], tokens_count_char, sizeof(&tokens_count_char)); //first element of array is count of tokens
    for (int i = 1; i < tokens_count_int + 1; i++) {
        char token[MAX_SIZE];
        strncpy_s(token, sizeof(token), buffer, (strstr(buffer, ";")) - buffer + 1);
        delete_current_token(buffer, strstr(buffer, ";") - buffer + 1);
        strncpy_s(tokens[i], sizeof(token), token, sizeof(token));
    }
    return tokens;
}

void delete_current_token(char* buffer, int j) {
    int i = 0;
    while ((buffer[i] = buffer[j++]) != '\0')
        i++;
}
