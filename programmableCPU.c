#include <stdio.h>
#include <string.h>
#include <math.h>
#include "directives.c"
#include "functions.c"
#include "stack.c"

#define NUMREG 16 //number of registries
#define ROMLINES 1024 //numbers of lines in rom
#define REGSIZE 8 //how big the values stored in the regs are
#define DIRSIZE 20 //how big the directives are

//specs        +1 for null operator
char registry[NUMREG][REGSIZE+1];
char ROM[ROMLINES][DIRSIZE+1];
STACK * stack = NULL;
STACK * temp;

//flags
typedef struct {unsigned int val:1;} FLAG;
FLAG Z; 
FLAG J; //jump flag

//necescarry
void init(); //for initializing the registries and the rom
void RUN();

int main(int, char *argv[]) {
    init();
    readProgram(ROM, argv[2]);
    RUN();
    return 0;
}

void RUN() {
    int PC = 0; //programm counter
    int OPCODE, ARG1, ARG2, ARG3, ARGJ; //code and arguments
    int num1, num2, in;
    Z.val = 0;

    while(strcmp(ROM[PC], "EOF")!=0) {
        J.val = 0;
        DECDIR(ROM[PC], &OPCODE, &ARG1, &ARG2, &ARG3, &ARGJ); //decoding directive from rom
        switch (OPCODE) {
            case ADD :
                num1 = STI(registry[ARG2]);
                num2 = STI(registry[ARG3]);
                strcpy(registry[ARG1], ITS(num1 + num2, REGSIZE));

                if (num1+num2> pow(2, REGSIZE) -1) return;
                Z.val = (num1+num2)==0;
                break;

            case SUB :
                num1 = STI(registry[ARG2]);
                num2 = STI(registry[ARG3]);
                strcpy(registry[ARG1], ITS(num1 - num2, REGSIZE));

                if (num1-num2> pow(2, REGSIZE) -1) return;
                Z.val = (num1-num2)==0;
                break;

            case AND :
                num1 = STI(registry[ARG2]);
                num2 = STI(registry[ARG3]);
                strcpy(registry[ARG1], ITS(num1 & num2, REGSIZE));

                Z.val = (num1&num2)==0;
                break;

            case OR  :
                num1 = STI(registry[ARG2]);
                num2 = STI(registry[ARG3]);
                strcpy(registry[ARG1], ITS(num1 | num2, REGSIZE));

                Z.val = (num1|num2)==0;
                break;

            case XOR :
                num1 = STI(registry[ARG2]);
                num2 = STI(registry[ARG3]);
                strcpy(registry[ARG1], ITS(num1 ^ num2, REGSIZE));

                Z.val = (num1^num2)==0;
                break;

            case NOT :
                num1 = STI(registry[ARG2]);
                strcpy(registry[ARG1], ITS(~num1, REGSIZE));

                Z.val = (~num1)==0;
                break;

            case MOV :
                strcpy(registry[ARG2], ITS(ARG1, REGSIZE));
                break;

            case JMP :
                PC = ARGJ;
                J.val = 1;
                break;

            case JPN :
                PC = (Z.val) ? ARGJ : PC;
                J.val = (Z.val) ? 1 : 0;
                break;

            case JPNZ:
                PC = (!Z.val) ? ARGJ : PC;
                J.val = (Z.val) ? 1 : 0;
                break;

            case CMP :
                num1 = STI(registry[ARG2]);
                num2 = STI(registry[ARG3]);
                if (num1==num2) strcpy(registry[ARG1], ITS(0, REGSIZE));
                else if (num1>num2) strcpy(registry[ARG1], ITS(1, REGSIZE));
                else strcpy(registry[ARG1], ITS(2, REGSIZE));
                break;

            case NOP :
                break;

            case LBSH:
                push(&stack, ARG1);
                strcpy(registry[NUMREG-1], ITS(stack->value, REGSIZE));
                break;

            case RBSH:
                pop(&stack);
                strcpy(registry[NUMREG-1], ITS(stack->value, REGSIZE));
                break;

            case DISP:
                push(&stack, STI(registry[ARG1]));
                strcpy(registry[NUMREG-1], ITS(stack->value, REGSIZE));
                break;

            default:
                break;
        }
        PC += (!J.val) ? 1 : 0;

        for(int i = 0; i<NUMREG; i++) { //print numbers
            printf("%d\t", STI(registry[i]));
            if ((i+1)%4==0) puts("");
        }
        puts("\n");
        temp = stack;
        for(; temp!=NULL;) {
            printf("%d\t", temp->value);
            temp = temp->previous;
        }
        puts("");
        /*temp = stack;
        for(; temp!=NULL;) {
            printf("%c\t", (char) (temp->value%256));
            temp = temp->previous;
        }*/
        puts("\n");
    }
}

void init() {
    for (int i = 0; i<NUMREG; i++) strcpy(registry[i], "\0");
    for (int j = 0; j<ROMLINES; j++) strcpy(ROM[j], "\0");
}