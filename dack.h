#ifndef DACK_H
#define DACK_H

#include "queue.h"

typedef struct NODE {
    int data;
    struct NODE* prev;
    struct NODE* next;
} NODE;

typedef struct {
    NODE* top;  
    NODE* end;   
    int size;     
} DACK;

void init_dack(DACK * dack);
int is_empty_dack(DACK * dack);
void add_end_dack(DACK * dack, int value);
void add_begin_dack(DACK * dack, int value);
int delete_begin_dack(DACK * dack);
int dalete_end_dack(DACK * dack);
void print_dack(DACK * dack);
int peek_begin_dack(DACK * dack);
int peek_end_dack(DACK * dack);
void input_dack(DACK * dack);
void free_dack(DACK * dack);
void find_two_negative(DACK * dack);

#endif