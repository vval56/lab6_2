#include "dack.h"

void init_dack(DACK * dack){
    dack->top = dack->end = NULL;
    dack->size = 0;
}

int is_empty_dack(DACK * dack){
    return dack->size == 0;
}

void add_end_dack(DACK * dack, int value){
    NODE * new_NODE = (NODE*)malloc(sizeof(NODE));
    new_NODE->data = value;
    new_NODE->next = NULL;
    new_NODE->prev = dack->end;

    if(is_empty_dack(dack)){
        dack->top = new_NODE;
    }
    else{
        dack->end->next = new_NODE;
    }

    dack->end = new_NODE;
    dack->size++;
}

void add_begin_dack(DACK *dack, int value) {
    NODE *new_NODE = (NODE*)malloc(sizeof(NODE));
    if (!new_NODE) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    
    new_NODE->data = value;
    new_NODE->prev = NULL;
    new_NODE->next = dack->top;

    if (is_empty_dack(dack)) {
        dack->end = new_NODE;
    } else {
        dack->top->prev = new_NODE;
    }
    
    dack->top = new_NODE;
    dack->size++;
}

int delete_begin_dack(DACK * dack){
    if(is_empty_dack(dack)){
        puts("Пустой дэк, заполните его");
        return -1;
    }

    int value = dack->top->data;

    dack->top = dack->top->next;

    if(dack->top == NULL){
        dack->end = NULL;
    }
    else{
        dack->top->prev = NULL;
    }

    dack->size--;
    return value;
}

int dalete_end_dack(DACK * dack){
    if(is_empty_dack(dack)){
        puts("Пустой дэк, заполните его");
        return -1;
    }

    int value = dack->end->data;

    dack->end = dack->end->prev;

    if(dack->end == NULL){
        dack->top = NULL;
    }
    else{
        dack->end->next = NULL;
    }

    dack->size--;
    return value;
}

void print_dack(DACK * dack){
    NODE * current = dack->top;
    printf("дэк размера %d: \n[", dack->size);
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }

    printf("]");
}

int peek_begin_dack(DACK * dack){
    if(is_empty_dack(dack)){
        puts("Пустой дэк, заполните его");
        return -1;
    }
    else{
        return dack->top->data;
    }
}

int peek_end_dack(DACK * dack){
    if(is_empty_dack(dack)){
        puts("Пустой дэк, заполните его");
        return -1;
    }
    else{
        return dack->end->data;
    }
}

void input_dack(DACK * dack){
    int size = 0, i = 0;
    char * line = NULL;

    puts("Введите размер дэк");
    do{
        size_t len;
        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            return;
        }
    } while (!check_int(&size, line) || size <= 0);

    init_dack(dack);
    free(line);

    puts("Введите целые числа (пустая строчка для завершения)");
    do{
        int number = 0;size_t len;

        printf("Значение №%d дэкa ", i + 1);
        
        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            return;
        }

        if (empty_line(line)) {
            break;
        }

        if(check_int(&number, line)){
            add_begin_dack(dack, number);
        }

        if(i == 0 && empty_line(line)){
            puts("дэк пуста, введите пожалуйста значение");
        }

        i++;

    }while(i < size);
}

void free_dack(DACK * dack) {
    while (!is_empty_dack(dack)) {
        delete_begin_dack(dack);
    }
}

void find_two_negative(DACK *dack) {
    input_dack(dack);
    
    NODE *current = dack->top;
    int negative_numbers[2] = {0};  
    int found = 0;
    
    while (current != NULL && found < 2) {
        if (current->data < 0) {
            negative_numbers[found] = current->data;
            found++;
        }
        current = current->next;
    }

    puts("");
    
    if (found == 0) {
        puts("Не нашлось отрицательных чисел");
    } else {
        for (int i = 0; i < found; i++) {
            printf("%d-е отрицательное число: %d\n", i+1, negative_numbers[i]);
        }
    }
    
    free_dack(dack);
}