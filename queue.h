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

#endif