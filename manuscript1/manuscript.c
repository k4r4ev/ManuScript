// manuscript.cpp: определяет точку входа для приложения.
//

#include "manuscript.h"
#include "lexer.h"
#include "variables.h"
#include "parser.h"
#include "time.h"

int main() {
    struct variable* vars_linked_list_head = NULL; //linked list for variables
    char buffer[MAX_SIZE] = { 0 };

    while (gets_s(buffer, MAX_SIZE)) {
        if (strlen(buffer) == 0) break;
        unsigned int start_time = clock();
        char** tokens = lexer(buffer);  //two-dimensional array for tokens
        const int tokens_count = strtol(tokens[0], NULL, 10);
        for (int i = 1; i <= tokens_count; i++) {
            parser(tokens[i], &vars_linked_list_head);
            printf("milliseconds: %lu\n", clock() - start_time);
        }
    }
    return 0;
}
