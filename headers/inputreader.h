#ifndef H_INPUTREADER
#define H_INPUTREADER

typedef struct value_has_comma_struct {
    int value;
    int has_comma;
} value_read;
#include "board.h"

int get_algorithm_from_input(char *input);
void get_value_from_string(value_read *res,char string[], int is_last);
int get_matrixes_from_input(int argc,char *argv[]);

char alt_get_value_from_string(char string[], int is_last);
int alt_method(int argc,char *argv[], all_boards *boards);

#endif
