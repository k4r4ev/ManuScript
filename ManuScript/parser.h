#pragma once

#include "main.h"

void parser(char*);
double expression(char*);
double element(char*, int*);
double function(char*, int*);
double number(char*, int*);
char* brackets(const char*, int*);
