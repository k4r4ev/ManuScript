#pragma once

#include "main.h"

struct variable {
    char name[MAX_SIZE];
    double value;
    struct variable *next;
};

void pushVariable(struct variable **, char *, double);

double getValueByVarName(struct variable **, char *);
