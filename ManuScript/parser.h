#pragma once

#include "main.h"
#include "functions.h"
#include "variables.h"

void parser(char*, struct variable**);
double expression(char*);
double element(char*, int*);
double function(char*, int*);
double number(char*, int*);
char* brackets(char*, int*);
