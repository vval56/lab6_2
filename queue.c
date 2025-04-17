#include "queue.h"

#define INT_MAX 32767
#define INT_MIN -32768

int check_int(int *number, char *line) {
    if (line == NULL || line[0] == '\n') {
        return 0;
    }

    int i = 0, sign = 1;
    *number = 0;

    if (line[i] == '-') {
        sign = -1;
        i++;
    }

    while (line[i] != '\0' && line[i] != '\n') {
        if (line[i] < '0' && line[i] > '9') {
            puts("Неверный ввод: допускаются только цифры");
            return 0;
        }
        *number = (*number * 10) + (line[i] - '0');
        i++;
    }

    if (*number > INT_MAX/10 || (*number == INT_MAX/10 && (line[i]-'0') > INT_MAX%10)) {
        puts("Превышено максимальное значение int");
        return 0;
    }

    *number *= sign;
    return 1;
}

int empty_line(char *line) {
    return (line == NULL || line[0] == '\n');
}

void init_queue(QUEUE * queue){
    queue->top = queue->end = NULL;
    queue->size = 0;
}

int is_empty_queue(QUEUE * queue){
    return queue->size == 0;
}

void add_element_queue(QUEUE *queue, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = queue->end;

    if (is_empty_queue(queue)) {
        queue->top = new_node;
    } else {
        queue->end->next = new_node;
    }
    
    queue->end = new_node;
    queue->size++;
}

int peek(QUEUE * queue) {
    if (is_empty_queue(queue)) {
        printf("Очередь пуста!\n");
        return -1;
    }
    return queue->top->data;
}

int delete_element_queue(QUEUE * queue){
    if(is_empty_queue(queue)){
        puts("пустая очередь. Невозможно удалить");
        return -1;
    }

    int value = queue->top->data;

    queue->top = queue->top->next;

    if(queue->top == NULL){
        queue->end = NULL;
    }
    else{
        queue->top->prev = NULL;
    }

    queue->size--;

    return value;
}

void print_queue(QUEUE * queue){
    Node * current = queue->top;
    printf("очередь размера: %d \n[", queue->size);
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }

    printf("]");
}

void input_queue(QUEUE * queue){
    int size = 0, i = 0;
    char * line = NULL;

    puts("Введите размер очереди");
    do{
        size_t len;
        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            return;
        }
    } while (!check_int(&size, line) || size <= 0);

    init_queue(queue);

    puts("Введите целые числа (пустая строчка для завершения)");
    do{
        int number = 0;size_t len;

        printf("Значение №%d очереди ", i + 1);
        
        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            return;
        }

        if (empty_line(line)) {
            break;
        }

        if(check_int(&number, line)){
            add_element_queue(queue, number);
        }

        if(i == 0 && empty_line(line)){
            puts("Очередь пуста, введите пожалуйста значение");
        }

        i++;

    }while(i < size);

}

void free_queue(QUEUE * queue) {
    while (!is_empty_queue(queue)) {
        delete_element_queue(queue);
    }
}

void find_negative_elements(QUEUE *queue) {
    input_queue(queue);

    Node *current = queue->top;
    int negative_numbers[2] = {0};  

    while (current != NULL && (negative_numbers[0] >= 0 || negative_numbers[1] >= 0)) {
        if (current->data < 0) {
            if (negative_numbers[0] >= 0) {
                negative_numbers[0] = current->data;
            } else if (negative_numbers[1] >= 0) {
                negative_numbers[1] = current->data;
            }
        }
        current = current->next;
    }

    int found = 0;
    for (int i = 0; i < 2; i++) {
        if (negative_numbers[i] < 0) {
            printf("%d-е отрицательное число: %d\n", i+1, negative_numbers[i]);
            found = 1;
        }
    }

    if (!found) {
        puts("Не нашлось отрицательных чисел");
    }

    free_queue(queue);
}