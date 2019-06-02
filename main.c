#include <stdio.h>

#include "stack.h"
#include "colors.h"
#include "bitcode.h"
#include "registers.h"

static int fact[] = {
    /*
     * EAX: initial value
     * EBX: iteration count
     * ECX: accumulator
     * 
     * pseudocode:
     * while starting val > iteration count
     *     accumulator *= iteration count
     */
    POP, EAX, // set up init val
    PSH, 1,
    POP, EBX, // set up iter count
    PSH, 1,
    POP, ECX, // set up acc

    LDR, EAX, // load value into stack
    LDR, EBX, // load iters into stack
    CMP,      // compare them
    JGT, 4,   // jump ahead as long as EAX > EBX
    LDR, ECX, // push acc to stack
    RET,      // EAX <= EBX, Return accumulator
    LDR, ECX, // load accumulator
    MLT,      // ECX * EBX
    POP, ECX, // save acc
    LDR, EBX, // load iter count
    INC,      // increment iter count
    POP, EBX, // store in EBX
    JMP, -21, // jump to start
};

static int fact_size = sizeof(fact) / sizeof(fact[0]);

static int maths[] = {
    PSH, 1232,
    PSH, 2,
    DIV,
    POP, EAX,
    PSH, 432432,
    LDR, EAX,
    MLT,
};

static int maths_size = sizeof(maths) / sizeof(maths[0]);

int main()
{
    FILE *out = fopen("maths", "w");
    fwrite((void *) &maths, sizeof(int), maths_size, out);
    fclose(out);

    stack *s = new_stack();
    registers r = { 0 };

    // Argument:
    stack_push(s, 5);

    execute(maths, maths_size, s, r);
    printf(C_CYAN "Result: %d\n" C_RESET, stack_pop(s));

    free_stack(s);
}
