#pragma once

#include "main.h"

void pushVariable(struct variable**, char*, double);
double getValueByVarName(struct variable**, char*);

struct variable {
	char name[MAX_SIZE];
	double value;
	struct variable* next;
};
