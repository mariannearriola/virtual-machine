#include <stdio.h>
#include <ctype.h>
#include <math.h>

typedef enum Op {
    NOP = 0x00,
    ADD = 0x01,
    SUB = 0x02,
    AND = 0x03,
    ORR = 0x04,
    XOR = 0x05,
    NOT = 0x06,
    LSH = 0x07,
    ASH = 0x08,
    TCU = 0x09,
    TCS = 0x0a,
    SET = 0x0b,
    MOV = 0x0c,
    LDW = 0x0d,
    STW = 0x0e,
    LDB = 0x0f,
    STB = 0x10
} Op;

/*int toDec(char* hex) {
    if(isdigit(hex[1])!=0) { return 0; }
    int dig = 0;
        switch(hex[1]) {
            case 'a':
                dig=10; break;
            case 'b':
                dig=11; break;
            case 'c':
                dig=12; break;
            case 'd':
                dig=13; break;
            case 'e':
                dig=14; break;
            case 'f':
                dig=15; break;
        
        }
     return dig;
}*/

typedef enum Reg {
    PC = 0x00,
    R1 = 0x01,
    R2 = 0x02,
    R3 = 0x03,
    R4 = 0x04,
    R5 = 0x05,
    R6 = 0x06,
    R7 = 0x07,
    R8 = 0x08,
    R9 = 0x09,
    R10 = 0x0a,
    R11 = 0x0b,
    R12 = 0x0c,
    R13 = 0x0d,
    R14 = 0x0e,
    R15 = 0x0f,
    R16 = 0x10,
    R17 = 0x11,
    R18 = 0x12,
    R19 = 0x13,
    R20 = 0x14,
    R21 = 0x15,
    R22 = 0x16,
    R23 = 0x17,
    R24 = 0x18,
    R25 = 0x19,
    R26 = 0x1a,
    R27 = 0x1b,
    R28 = 0x1c,
    R29 = 0x1d,
    AT = 0x1e,
    SP = 0x1f,
} Reg;
