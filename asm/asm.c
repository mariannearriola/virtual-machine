#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "asm.h"

int main(int argc, char* argv[]) {
    // reading files
    FILE *input = fopen(argv[1],"r");
    FILE *output = fopen(argv[2],"w+");
    char line[256];
    while(fgets(line,sizeof(line),input)) {
        // retrieving line
        line[strlen(line)-1] = '\0';
        char* op = (char*)malloc(100); 
        char* arg1 = (char*)malloc(100);
        char* arg2 = (char*)malloc(100);
        char* arg3 = (char*)malloc(100);
        char *tok;
        tok = strtok(line, " ");
        if(tok != NULL) { 
            strcpy(op,tok);
            tok = strtok(NULL," ");
        }
        if(tok != NULL) {
            strcpy(arg1,tok);
            tok = strtok(NULL," ");
        }
        if(tok != NULL) {
            strcpy(arg2,tok);
            tok = strtok(NULL," ");
        }
        if(tok != NULL) { strcpy(arg3,tok); }
        // assigning bytes
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
        uint8_t b4;
        char instr[8] = {'0'};

        int opCode;
        for(int i = 0; i < 17; i++) {
            if(!strcmp(op,ops[i])) { opCode = i; } 
        }

        switch(opCode) {
            case 0:
                //b1 = b2 = b3 = b4 = 0;
                break;
            // three args
            case 0x01:
            case 0x02:
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x07:
            case 0x08:
            case 0x09:
            case 0x0a:
                b1 = opCode; 
                for(int i = 0; i < 32; i++) {
                    if(!strcmp(arg1,regs[i])) { b2 = i; }
                    if(!strcmp(arg2,regs[i])) { b3 = i; }
                    if(!strcmp(arg3,regs[i])) { b4 = i; }
                }
                break;
            // two args
            case 0x06:
            case 0x0c:
            case 0x0d:
            case 0x0e:
            case 0x0f:
            case 0x10:
                b1 = opCode;
                for(int i = 0; i < 32; i++) {
                    if(!strcmp(arg1,regs[i])) { b2 = i; }
                    if(!strcmp(arg2,regs[i])) { b3 = i; }
                }
                b4 = 0;
                break;
            // set
            case 0x0b:
                b1 = opCode;
                for(int i = 0; i < 32; i++) {
                    if(!strcmp(arg1,regs[i])) { 
                        b2 = i;
                        break;
                    }
                }
                b3 = atoi(arg2);
                b4 = 0;
                break;
        }
        fwrite(&b1,1,1,output);
        fwrite(&b2,1,1,output);
        fwrite(&b3,1,1,output);
        fwrite(&b4,1,1,output);
    }
    fclose(input);
    fclose(output);
    return 0;
}
