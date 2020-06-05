#include "parser.h"

void parser(char* string, struct variable** vars_linked_list_head) {
    char buffer[MAX_SIZE] = { 0 };
    double value = 0.0;
    char* variable = 0;
    char* function = 0;
    char* argument = 0;
    int i = 0, k = 0;
    for (i; (string[i] != '(') && (string[i] != '=') && (string[i] != ';') && (string[i] != '\0'); i++) {
        buffer[i] = string[i]; //getting the name of function or variable
    }
    switch (string[i]) {
    case '(':
        i++;
        function = buffer; //save function name
        argument = brackets(string, &i);
        text_function(function, argument);
        break;
    case '=':
        variable = buffer; //save variable name
        while ((string[k] = string[++i]) != '\0') //delete everything before the equal
            k++;
        string[--k] = '\0'; //remove the semicolon
        value = expression(vars_linked_list_head, string); //calculating
        push_variable(vars_linked_list_head, variable, value);
        printf("\t%s = %lf\n", variable, get_value_by_var_name(vars_linked_list_head, variable)); //printing the variable
        break;
    default:
        break;
    }
}

static double expression(struct variable** vars_linked_list_head, char* buffer) {
    int index = 0; //current position
    double value = element(vars_linked_list_head, buffer, &index); //getting the first element
    for (;;) {
        switch (buffer[index++]) //current symbol
        {
        case '\0':
            return value;
        case '+':
            value += element(vars_linked_list_head, buffer, &index);
            break;
        case '-':
            value -= element(vars_linked_list_head, buffer, &index);
            break;
        default: //removing everything else
            continue;
        }
    }
}

double element(struct variable** vars_linked_list_head, char* buffer, int* index) {
    double value = function(vars_linked_list_head, buffer, index); //get the first number
    printf("first:%lf\n", value);
    printf("index:%c\n", (buffer[*index]));
    while ((buffer[*index] == '*') || (buffer[*index] == '/')) {
        if (buffer[*index] == '*') {
            *index = *index + 1;
            //printf("second:%lf\n", function(vars_linked_list_head, buffer, index));
            value *= function(vars_linked_list_head, buffer, index);
        }
        if (buffer[*index] == '/') {
            *index = *index + 1;
            value /= function(vars_linked_list_head, buffer, index);
        }
        //if (buffer[*index] == '/') {}
    }
    return value;
}

double function(struct variable** vars_linked_list_head, char* buffer, int* index) {
    int buf_index = 0;
    double value = 0.0;
    while (isalpha(buffer[*index])) { //is character
        buf_index++; //how many symbols
        *index = *index + 1;
    }
    if (!buf_index) { //if there are no characters
        value = number(vars_linked_list_head, buffer, index);
        return value;
    }
    //if there are characters (there is a function)
    char* function_name = malloc(buf_index + 1); //temporary pointer to compare characters
    function_name[buf_index] = '\0';
    strncpy_s(function_name, sizeof(function_name), buffer + (*index - buf_index), buf_index);
    if (isalpha(buffer[*index + 1])) { //if the first element of argument is character
        buf_index = 0;
        *index = *index + 1;
        while (buffer[*index] != ')') {
            buf_index++;
            *index = *index + 1;
        }
        char* arg = malloc(buf_index + 1);
        strncpy_s(arg, sizeof(arg), buffer + (*index - buf_index), buf_index);
        value = vars_function(vars_linked_list_head, function_name, arg);
        *index = *index + 1; //skip the '('
        return value;
    }
    return math_function(function_name, number(vars_linked_list_head, buffer, index));
}


double number(struct variable** vars_linked_list_head, char* buffer, int* index) {
    double value = 0.0; //result
    if (buffer[*index] == '(') {
        *index = *index + 1;
        char* p_substr = 0;
        p_substr = brackets(buffer, index);
        value = expression(vars_linked_list_head, p_substr);
        return value;
    }
    while (isdigit(buffer[*index])) { //convert chars to number
        char p_str = buffer[*index];
        value = 10 * value + strtod(&p_str, NULL);
        *index = *index + 1;
    }
    if ((buffer[*index] != '.') && (buffer[*index] != ',')) { //if it is a float
        return value;
    }
    double factor = 1.0; //multiplier
    *index = *index + 1;
    while (isdigit(buffer[*index])) {
        factor *= 0.1;
        value = value + strtod(&buffer[*index], NULL) * factor;
        *index = *index + 1;
    }
    return value;
}

char* brackets(const char* buffer, int* index) {
    char buf[128];    //for substring
    char* p_str = (char*)malloc(MAX_SIZE);    //pointer to new string
    int num_l = 0;    //left brackets count
    const int buf_index = *index;
    do {
        buf[*index - buf_index] = buffer[*index];
        switch (buf[*index - buf_index]) {
        case ')':
            if (num_l == 0) {
                buf[*index - buf_index] = '\0';
                *index = *index + 1;
                strncpy_s(p_str, MAX_SIZE, buf, MAX_SIZE);
                if (p_str != 0) return p_str;
            }
            else
                num_l--;
            break;
        case '(':
            num_l++;
            break;
        }
        *index = *index + 1;
    } while (buffer[*index] != '\0');
    return p_str;
}
