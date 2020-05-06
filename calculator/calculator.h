#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef enum {
    TOKEN_OPERATOR,
    TOKEN_NUMBER
}token_type_e;

typedef struct {
    token_type_e type;
    int val;
}token_t;

typedef struct {
    int top;
    int *info;
}stack;

typedef struct {
    int front;
    int back;
    token_t *info;
}queue;


// STACK

void st_init(stack *s) {
    s->top = -1;
    s->info = malloc(0);
}

void st_push(int info, stack *s) {
    s->info = (int*) realloc(s->info,(((s->top + 1)*sizeof(int))+1));
    s->top++;
    s->info[s->top] = info;
}

int st_empty(const stack *s) {
    return s->top == -1;
}

int st_pop(stack *s) {
    if (st_empty(s))
    {
        return -1;
    }

    return s->info[s->top--];
}

int peek(const stack *s) {
    if (st_empty(s)) {
        return -1;
    }
    return s->info[s->top];
}

    // QUEUE
    
void qu_init(queue* q) {
    q->front = q->back = -1;
    q->info = malloc(0);
    //memset(q->info, 0x00, sizeof(q->info));
}

void enq(token_t info, queue* q) {
    q->info = (token_t*) realloc(q->info,(((q->back + 1)*sizeof(token_t))+1));
    if (q->front == -1) {
        q->front = 0;
    }
    q->back++;
    q->info[q->back] = info;
}

int qu_empty(const queue* q) {
    return (q->front == -1 || q->front > q->back);
}

token_t deq (queue* q) {
    return q->info[q->front++];
}

int precedence(char op) {
    int out = 0;
    if (op == '+' || op == '-') {
        out = 2;
    }
    else if (op == '*' || op == '/' || op == '%') {
        out = 3;
    }
    else if (op == '^') {
        out = 4;
    }
    return out;
}
int calculate(char* expression);

#endif
