#include "string_sum.h"
#include <stdio.h>
#include <stdlib.h>

int is_empty_QUEUE_DOUBLE(QUEUE_DOUBLE *queue) {
    return queue->size == 0;
}

void init_QUEUE_DOUBLE(QUEUE_DOUBLE *queue) {
    queue->top = queue->end = NULL;
    queue->size = 0;
}

void print_QUEUE_DOUBLE(QUEUE_DOUBLE *queue) {
    if (is_empty_QUEUE_DOUBLE(queue)) {
        printf("Очередь пуста\n");
        return;
    }

    ELEM *current = queue->top;
    printf("Очередь (размер %d): [", queue->size);
    
    while (current != NULL) {
        if (current->data == (int)current->data) {
            printf("%d", (int)current->data); 
        } else {
            printf("%.2f", current->data); 
        }
        
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void add_element_QUEUE_DOUBLE(QUEUE_DOUBLE *queue, double value) {
    ELEM *new_elem = (ELEM*)malloc(sizeof(ELEM));
    if (!new_elem) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    
    new_elem->data = value;
    new_elem->next = NULL;
    new_elem->prev = queue->end;

    if (is_empty_QUEUE_DOUBLE(queue)) {
        queue->top = new_elem;
    } else {
        queue->end->next = new_elem;
    }
    
    queue->end = new_elem;
    queue->size++;
}

double delete_element_QUEUE_DOUBLE(QUEUE_DOUBLE *queue) {
    if (is_empty_QUEUE_DOUBLE(queue)) {
        puts("Очередь пуста");
        return 0.0;
    }

    ELEM *temp = queue->top;
    double value = temp->data;

    queue->top = queue->top->next;
    if (queue->top == NULL) {
        queue->end = NULL;
    } else {
        queue->top->prev = NULL;
    }

    free(temp);
    queue->size--;
    return value;
}

void free_QUEUE_DOUBLE(QUEUE_DOUBLE *queue) {
    while (!is_empty_QUEUE_DOUBLE(queue)) {
        delete_element_QUEUE_DOUBLE(queue);
    }
}

void input_text(char ***text) {
    int rows = 0;
    *text = NULL;
    char *line = NULL;
    size_t length = 0;

    puts("Введите текст (пустая строка для завершения):");
    while (1) {
        int read = getline(&line, &length, stdin);

        if (read == -1) {
            puts("Ошибка ввода");
            free(line);
            if (*text) {
                for (int i = 0; i < rows; i++) {
                    free((*text)[i]);
                }
                free(*text);
            }
            exit(EXIT_FAILURE);
        }

        if (read == 1 && line[0] == '\n') {
            free(line);
            line = NULL;
            break;
        }

        char **temp = realloc(*text, sizeof(char*) * (rows + 1));
        if (!temp) {
            puts("Ошибка перераспределения памяти");
            free(line);
            if (*text) {
                for (int i = 0; i < rows; i++) {
                    free((*text)[i]);
                }
                free(*text);
            }
            exit(EXIT_FAILURE);
        }
        *text = temp;

        (*text)[rows] = malloc(read + 1);
        if (!(*text)[rows]) {
            puts("Ошибка выделения памяти для строки");
            free(line);
            for (int i = 0; i < rows; i++) {
                free((*text)[i]);
            }
            free(*text);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < read; i++) {
            (*text)[rows][i] = line[i];
        }
        (*text)[rows][read] = '\0';
        rows++;
    }

    char **temp = realloc(*text, sizeof(char*) * (rows + 1));
    if (!temp && rows > 0) {
        for (int i = 0; i < rows; i++) {
            free((*text)[i]);
        }
        free(*text);
        exit(EXIT_FAILURE);
    }
    *text = temp;
    (*text)[rows] = NULL;

    if (line) {
        free(line);
    }
}

static int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static int is_number_char(char c) {
    return is_digit(c) || c == '.' || c == '-';
}

static void process_number(char *str, int *pos, QUEUE_DOUBLE *queue) {
    int i = *pos;
    int sign = 1;
    double number = 0.0;
    double fraction = 0.0;
    int has_fraction = 0;
    int fraction_digits = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (is_digit(str[i])) {
        number = number * 10 + (str[i] - '0');
        i++;
    }

    if (str[i] == '.') {
        has_fraction = 1;
        i++;
        while (is_digit(str[i])) {
            fraction = fraction * 10 + (str[i] - '0');
            fraction_digits++;
            i++;
        }
    }

    if (has_fraction) {
        for (int j = 0; j < fraction_digits; j++) {
            fraction /= 10.0;
        }
        number += fraction;
    }

    number *= sign;
    add_element_QUEUE_DOUBLE(queue, number);
    *pos = i;
}

void numbers_from_line_to_QUEUE_DOUBLE(char ***text, QUEUE_DOUBLE *queue) {
    if (!text || !*text) return;

    for (int row = 0; (*text)[row] != NULL; row++) {
        int i = 0;
        while ((*text)[row][i] != '\0') {
            if (is_number_char((*text)[row][i])) {
                process_number((*text)[row], &i, queue);
            } else {
                i++;
            }
        }
    }
}

double sum_elements_QUEUE_DOUBLE(QUEUE_DOUBLE *queue) {
    double sum = 0.0;
    ELEM *current = queue->top;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

void sum_numbers() {
    char **text = NULL;
    QUEUE_DOUBLE queue;
    init_QUEUE_DOUBLE(&queue);

    input_text(&text);
    numbers_from_line_to_QUEUE_DOUBLE(&text, &queue);

    print_QUEUE_DOUBLE(&queue);

    printf("\nСумма элементов очереди: %.2f\n", sum_elements_QUEUE_DOUBLE(&queue));

    if (text) {
        for (int i = 0; text[i] != NULL; i++) {
            free(text[i]);
        }
        free(text);
    }
    free_QUEUE_DOUBLE(&queue);
}