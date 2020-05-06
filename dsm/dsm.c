#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../vm/vm.h"

int main(int argc, char* argv[]) {
    // opening files
    FILE *input = fopen(argv[1],"rb");
    FILE *output = fopen(argv[2],"w+");

    // initializing variables
    uint32_t mem[10000];
    for(int i = 0; i < 10000; i++) { mem[i] = 0; }
    int pc = 0;
    int s = 0;
    while(1) {
        // reading input
        fread(&mem+s,4,1,input);
        if(feof(input)) { break; }
        uint8_t ops = mem[pc] >> 0;
        Op op = (Op) (int)ops;
        uint8_t rA = mem[pc] >> 8;
        uint8_t rB;
        uint8_t rC = mem[pc] >> 24;
        uint8_t imm;
        if(op == SET) { imm = mem[pc] >> 16; }
        else { rB = mem[pc] >> 16; }

        // reading binary
        switch(op) {
            //0x00
            case NOP:
                fprintf(output, "nop\n");
                break;
            //0x01
            case ADD:
                fprintf(output,"add r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x02
            case SUB:
                fprintf(output,"sub r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x03
            case AND:
                fprintf(output,"and r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x04
            case ORR:
                fprintf(output,"orr r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x05
            case XOR:
                fprintf(output,"xor r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x06
            case NOT:
                fprintf(output,"not r%u r%u\n",rA,rB);
                break;
            //0x07
            case LSH:
                fprintf(output,"lsh r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x08
            case ASH:
                fprintf(output,"ash r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x09
            case TCU:
                fprintf(output,"tcu r%u r%u r%u\n",rA,rB,rC);
                break;
             //0x0a
            case TCS:
                fprintf(output,"tcs r%u r%u r%u\n",rA,rB,rC);
                break;
            //0x0b
            case SET:
                fprintf(output,"set r%u %u\n",rA,imm);
                break;
            //0x0c
            case MOV:
                fprintf(output,"mov r%u r%u\n",rA,rB);
                break;
            //0x0d
            case LDW:
                fprintf(output,"ldw r%u r%u\n",rA,rB);
                break;
            //0x0e
            case STW:
                fprintf(output,"stw r%u r%u\n",rA,rB);
                break;
            //0x0f
            case LDB:
                fprintf(output,"ldb r%u r%u\n",rA,rB);
                break;
            //0x10
            case STB:
                fprintf(output,"stb r%u r%u\n",rA,rB);
                break;
            default:
                break;
        }
    }
    pc+=4;
    fclose(input);
    fclose(output);
    return 0;
}
