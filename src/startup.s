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
    b main
    