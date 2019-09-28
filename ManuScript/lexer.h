#pragma once

#include "main.h"

char** lexer(char*); //лексическая обработка
void spaces(char*);    //удаление пробелов
void squeeze(char*, int);  //удаление подстроки
char inverting(int);
