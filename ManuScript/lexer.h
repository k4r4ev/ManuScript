#pragma once

#include "main.h"

char **lexer(char *); //лексическая обработка

char **prepareTokens(char *); //подготовка токенов

void spacesRemoving(char *); //удаление пробелов

void deleteCurrentToken(char *, int); //удаление подстроки
