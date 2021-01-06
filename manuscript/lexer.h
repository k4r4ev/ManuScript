#pragma once

#include "manuscript.h"

char** lexer(char*);
char** prepare_tokens(char*);
void spaces_removing(char*);
void delete_current_token(char*, int);
