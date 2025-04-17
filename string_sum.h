#ifndef STRING_SUM_H
#define STRING_SUM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ELEM {
    double data; 
    struct ELEM* next;
    struct ELEM* prev;
} ELEM;

typedef struct {
    ELEM* top;
    ELEM* end;
    int size;
} QUEUE_DOUBLE;

int is_empty_QUEUE_DOUBLE(QUEUE_DOUBLE *queue);
void print_QUEUE_DOUBLE(QUEUE_DOUBLE *queue);
void init_QUEUE_DOUBLE(QUEUE_DOUBLE *queue);
void add_element_QUEUE_DOUBLE(QUEUE_DOUBLE *queue, double value);
double delete_element_QUEUE_DOUBLE(QUEUE_DOUBLE *queue);
void free_QUEUE_DOUBLE(QUEUE_DOUBLE *queue);
void input_text(char ***text);
void numbers_from_line_to_QUEUE_DOUBLE(char ***text, QUEUE_DOUBLE *queue);
double sum_elements_QUEUE_DOUBLE(QUEUE_DOUBLE *queue);
void sum_numbers();

#endif