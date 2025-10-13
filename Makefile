# compiler name
PREFIX   = arm-none-eabi
# compiler
CC 		 = ${PREFIX}-gcc
# compile flags
CFLAGS   = -c -g -O1 -mthumb
# linker flags
LDFLAGS  = -nostdlib
# cpu arch
CPU_ARCH = cortex-m4
# GDB
GDB      = ${PREFIX}-gdb

all:
	${CC} ${CFLAGS} -mcpu=${CPU_ARCH} main.c -o main.o	
	${CC} ${LDFLAGS} -T ld_ram.lds 	  main.o -o main.elf

clean:
	rm -rf *.o
	rm -rf *.elf

# debug infrastructure
connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhosstOnly

debug:
	${GDB} -x stm32-4se.gdb 
