#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    unsigned int value: 8;
    struct stack * previous;
} STACK;

STACK * newNode() {
    STACK * temp = calloc(1, sizeof(STACK));
    temp->value = 0;
    temp->previous = NULL;
    return temp;
}

void push(STACK ** cursor, int value) {
    STACK * head = newNode();
    head->value=value;
    head->previous=*cursor;
    *cursor=head;
}

void pop(STACK ** cursor) {
    if (*cursor==NULL) return;
    STACK * temp = (*cursor)->previous;
    free(*cursor);
    *cursor = temp;
}