#include <stdio.h>

#include "bitcode.h"
#include "stack.h"
#include "registers.h"
#include "colors.h"

void execute(int data[], int length, stack *s, stack *callstack, registers r)
{
    for (int i = 0; i < length; ++i)
    {
        printf(C_GREEN "____________________________\n" C_RESET);
        switch (data[i])
        {
            case PSH:
            {
                int val = data[++i];
                printf(C_BLUE "PSH" C_RESET " %d\n", val);

                stack_push(s, val);                
                break;
            } case POP:
            {
                int reg = data[++i];
                printf(C_BLUE "POP" C_RESET " %d\n", reg);

                r[reg] = stack_pop(s);
                break;
            } case LDR:
            {
                int reg = data[++i];
                printf(C_BLUE "LDR" C_RESET " %d\n", reg);

                stack_push(s, r[reg]);
                break;
            } case ADD:
            {
                printf(C_BLUE "ADD\n" C_RESET);

                int a = stack_pop(s);
                int b = stack_pop(s);
                stack_push(s, a + b);
                break;
            } case SUB:
            {
                printf(C_BLUE "SUB\n" C_RESET);

                int a = stack_pop(s);
                int b = stack_pop(s);
                stack_push(s, b - a);
                break;
            } case MLT:
            {
                printf(C_BLUE "MLT\n" C_RESET);

                int a = stack_pop(s);
                int b = stack_pop(s);
                stack_push(s, b * a);
                break;
            } case DIV:
            {
                printf(C_BLUE "DIV\n" C_RESET);

                int a = stack_pop(s);
                int b = stack_pop(s);
                stack_push(s, b / a);
                break;
            } case JMP:
            {
                int offset = data[++i];
                printf(C_BLUE "JMP" C_RESET " %d\n", offset);

                i += offset - 1;

                break;
            } case JPS:
            {
                printf(C_BLUE "JPS\n" C_RESET);
                int offset = stack_pop(s);

                i += offset - 1;

                break;
            } case CMP:
            {
                int a = stack_pop(s);
                int b = stack_pop(s);
                printf(C_BLUE "CMP\n" C_RESET);
                // ... b a
                r[LT] = 0;
                r[GT] = 0;
                r[EQ] = 0;

                if (b > a)
                    r[GT] = 1;
                else if (b < a)
                    r[LT] = 1;
                else
                    r[EQ] = 1;

                stack_push(s, b);
                stack_push(s, a);

                break;
            } case JGT:
            {
                int offset = data[++i];
                printf(C_BLUE "JGT" C_RESET " %d\n", offset);

                if (r[GT] == 1)
                    i += offset - 1;

                break;
            } case JLT:
            {
                int offset = data[++i];
                printf(C_BLUE "JLT" C_RESET " %d\n", offset);

                if (r[LT])
                    i += offset - 1;

                break;
            } case JEQ:
            {
                int offset = data[++i];
                printf(C_BLUE "JEQ" C_RESET " %d\n", offset);

                if (r[EQ])
                    i += offset - 1;

                break;
            } case JNE:
            {
                int offset = data[++i];
                printf(C_BLUE "JNE" C_RESET " %d\n", offset);
                if (!r[EQ])
                    i += offset - 1;

                break;
            } case DUP:
            {
                printf(C_BLUE "DUP\n" C_RESET);

                int a = stack_pop(s);
                stack_push(s, a);
                stack_push(s, a);
                break;
            } case INC:
            {
                printf(C_BLUE "INC\n" C_RESET);
                stack_push(s, stack_pop(s) + 1);
                break;
            } case DEC:
            {
                printf(C_BLUE "INC\n" C_RESET);
                stack_push(s, stack_pop(s) - 1);
                break;
            } case SWP:
            {
                printf(C_BLUE "SWP\n" C_RESET);
                int a = stack_pop(s);
                int b = stack_pop(s);
                stack_push(s, a);
                stack_push(s, b);
                break;
            } case RET:
            {
                printf(C_BLUE "RET\n" C_RESET);
                i = stack_pop(callstack);
                break;
            } case CAL:
            {
                int offset = data[++i];
                printf(C_BLUE "CAL" C_RESET " %d\n", offset);

                stack_push(callstack, i);

                i += offset - 1;
                break;
            } case END:
            {
                printf(C_BLUE "END\n" C_RESET);
                return;
            }
        }
        printf("lt: %d gt: %d eq: %d\n", r[LT], r[GT], r[EQ]);
        printf(C_YELLOW "EAX: %d EBX: %d ECX: %d EDX: %d\n" C_RESET, r[EAX], r[EBX], r[ECX], r[EDX]);
        stack_print(s);
    }
}
