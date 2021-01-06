# CMakeList.txt: проект CMake для manuscript; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (manuscript "manuscript.c" "manuscript.h" "lexer.c" "lexer.h" "parser.c" "parser.h" "variables.c" "variables.h" "functions.c" "functions.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
