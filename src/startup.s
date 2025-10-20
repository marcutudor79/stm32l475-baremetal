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

    # branch to main C program
    bl main