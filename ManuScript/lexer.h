#pragma once

#include "main.h"

char **lexer(char *); //����������� ���������

char **prepareTokens(char *); //���������� �������

void spacesRemoving(char *); //�������� ��������

void deleteCurrentToken(char *, int); //�������� ���������
