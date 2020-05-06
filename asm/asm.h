#include <stdio.h>

char ops[17][4] = {
    "nop",
    "add",
    "sub",
    "and",
    "orr",
    "xor",
    "not",
    "lsh",
    "ash",
    "tcu",
    "tcs",
    "set",
    "mov",
    "ldw",
    "stw",
    "ldb",
    "stb"
};

char regs[][4] = {
    "pc",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15",
    "r16",
    "r17",
    "r18",
    "r19",
    "r20",
    "r21",
    "r22",
    "r23",
    "r24",
    "r25",
    "r26",
    "r27",
    "r28",
    "r29",
    "at",
    "sp"
};

typedef struct Stmt {
    char *label;
    char *instr;
    char *params[3];
    struct statement *next;
} Stmt;

typedef struct Func {
    Stmt *head;
    Stmt *tail;
} Func;

typedef struct Stack {

} Stack;
