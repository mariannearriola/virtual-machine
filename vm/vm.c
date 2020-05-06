#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vm.h"

int main(int argc, char* argv[]) {
    FILE *file = fopen(argv[1],"rb"); 
    // registers
    uint32_t regs[32] = {0};
    
    // memory
    // use sizeof/memset/{}
    uint32_t memory[10000] = {0};
    
    uint32_t* pc = regs;
    uint32_t* sp = regs+31;
    uint32_t* at = regs+30;
    // file read
    int s = 0;
    while(fread(memory+s,4,1,file)==1) { s++; }
    //getc
    while(1) {
        // reading bin
        uint8_t ops = memory[*pc] >> 0;
        Op op = (Op) (int)ops;
        uint8_t rA = memory[*pc] >> 8;
        uint8_t rB;
        uint8_t rC = memory[*pc] >> 24;
        uint8_t imm;
        imm = memory[*pc] >> 16;
        rB = memory[*pc] >> 16;
        
        // printing
        printf("PREVIOUS STATE: \n");
        for(int i = 0; i < 32; i++) {
            printf("R%d:",i);
            printf("%d  ",regs[i]);
            if(i % 9 == 0) { printf("\n"); }
        }
        printf("\n");
        printf("\n");

        // operations
        switch(op) {
            //0x00
            case NOP:
                break;
            //0x01
            case ADD:
                regs[rA] = regs[rB] + regs[rC];
                break;
            //0x02
            case SUB:
                regs[rA] = regs[rB] - regs[rC];
                break;
            //0x03
            case AND:
                regs[rA] = regs[rB] & regs[rC];
                break;
            //0x04
            case ORR:
                regs[rA] = regs[rB] | regs[rC];
                break;
            //0x05
            case XOR:
                regs[rA] = regs[rB] ^ regs[rC];
                break;
            //0x06
            case NOT:
                regs[rA] = ~regs[rB];
                break;
            //0x07
            case LSH:
                if(regs[rC] > 32 || regs[rC] < -32) { break; }
                else if(regs[rC] > 0) { regs[rA] = regs[rB] << regs[rC]; }
                else { regs[rA] = regs[rB] >> abs(regs[rC]); }
                break;
            //0x08
            case ASH:
                if(regs[rC] > 32 || regs[rC] < -32) { break; }
                else if(regs[rC] > 0) { regs[rA] = (int32_t)regs[rB] << (int32_t)regs[rC]; }
                else { rA = (int32_t)regs[rB] >> abs((int32_t)regs[rC]); }
                break;
            //0x09
            //work on
            //if greater set to 1 / -1
            case TCU:
                if( regs[rC] - regs[rB] > 0 ) { regs[rA] = 1;  }
                else { regs[rA] = -1; }
                break;
             //0x0a
             //work on
            case TCS:
                if((int32_t)regs[rC]-(int32_t)regs[rB]>0) { regs[rA] = 1; }
                else { regs[rA] = -1; }
                break;
            //0x0b
            case SET:
                regs[rA] = (uint16_t)imm;
                break;
            //0x0c
            case MOV:
                regs[rA] = regs[rB];
                break;
            //0x0d
            case LDW:
                regs[rA] = memory[regs[rB]];
                break;
            //0x0e
            case STW:
                memory[regs[rA]] = regs[rB];
                break;
            //0x0f
            case LDB:
                regs[rA] = (uint8_t)memory[regs[rB]];
                break;
            //0x10
            case STB:
                memory[regs[rA]] = (uint8_t)regs[rB];
                break;
            default:
                break;
        }

        // printing
        printf("CURRENT STATE: \n");
        for(int i = 0; i < 32; i++) { 
            printf("R%d:",i);
            printf("%d  ",regs[i]);
            if(i % 9 == 0) { printf("\n"); }
        }
        printf("\n");
        printf("\n");

        // iterating
        *pc+=4;
        getchar();
    }
    fclose(file);
    return 0;
}
