#include "variables.h"

void push_variable(struct variable** head, char* name, const double value) {
    struct variable* tmp = (struct variable*)malloc(sizeof(struct variable));
    strcpy_s(tmp->name, sizeof(tmp->name), name);
    tmp->value = value;
    tmp->next = (*head);
    (*head) = tmp;
}

double get_value_by_var_name(struct variable** vars, char* name) {
    if (strcmp((*vars)->name, name) == 0) {
        return (*vars)->value;
    }
    struct variable* tmp = (*vars)->next;
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return 0.0;
}
