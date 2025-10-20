.syntax unified
.arch armv7e-m
.cpu cortex-m4

# use thumb instruction set
.thumb

# set the _start function as global function
.global _start
_start:
    # init the stack
    ldr sp, =_stack_start

    # go and init bss
    bl init_bss

    # branch to main C program
    bl main

# prevent execution of other parts of code if main exits (should never get here)
_exit:
    b _exit
