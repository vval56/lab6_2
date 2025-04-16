#include <stdio.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* top;  
    Node* end;   
    int size;     
} QUEUE;

int check_int(int *number, char *line);
int empty_line(char *line);
void init_queue(QUEUE * queue);
int is_empty_queue(QUEUE * queue);
void add_element_queue(QUEUE * queue, int value);
int peek(QUEUE * queue);
int delete_element_queue(QUEUE * queue);
void print_queue(QUEUE * queue);
void input_queue(QUEUE * queue);
void free_queue(QUEUE * queue);
void find_negative_elements(QUEUE * queue);

#endif