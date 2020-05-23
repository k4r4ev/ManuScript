#include "functions.h"

void text_function(char* function, char* args) {
    if (strcmp(function, "print") == 0) {
        printf("\t%s\n", args);
        return;
    }
    else if (strcmp(function, "clear") == 0) {
        system("cls");
        return;
    }
    else if (strcmp(function, "info") == 0) {
        printf("\tinfo\t-\tinformation about functions\n");
        printf("\tprint\t-\toutput function\n");
        printf("\tclear\t-\tclear console\n");
        printf("\tsin\t-\tsine of the function\n");
        printf("\tcos\t-\tcosine of the function\n");
        printf("\ttan\t-\ttangent of the function\n");
        printf("\tctg\t-\tcotangent of the function\n");
        return;
    }
    else {
        printf("\ttextFunction parser error\n");
        return;
    }
}

double math_function(char* function, double value) {
    if (strcmp(function, "sin") == 0) {
        value = sin(PI / 180 * value);
        return value;
    }
    else if (strcmp(function, "cos") == 0) {
        value = cos(PI / 180 * value);
        return value;
    }
    else if (strcmp(function, "tan") == 0) {
        value = tan(PI / 180 * value);
        return value;
    }
    else if (strcmp(function, "ctg") == 0) {
        value = 1 / tan(PI / 180 * value);
        return value;
    }
    else {
        printf("\tmathFunction parser error\n");
        return value;
    }
}

double vars_function(struct variable** vars_linked_list_head, char* function, char* args) {
    if (strcmp(function, "var") == 0) {
        return get_value_by_var_name(vars_linked_list_head, args);
    }
    else {
        printf("\tvarsFunction parser error\n");
        return 0.0;
    }
}
