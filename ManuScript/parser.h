#pragma once

#include "manuscript.h"
#include "functions.h"
#include "variables.h"

void parser(char*, struct variable**);
double expression(struct variable**, char*);
double element(struct variable**, char*, int*);
double function(struct variable**, char*, int*);
double number(struct variable**, char*, int*);
char* brackets(const char*, int*);
