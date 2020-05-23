#pragma once

#include "main.h"

struct variable {
    char name[MAX_SIZE];
    double value;
    struct variable *next;
};

void push_variable(struct variable **, char *, double);

double get_value_by_var_name(struct variable **, char *);
