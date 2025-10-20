# compiler name
PREFIX   = arm-none-eabi
# compiler
CC 		 = ${PREFIX}-gcc
# compile flags
CFLAGS   = -g -O0 -mthumb -ffreestanding
# linker flags
LDFLAGS  = -T ld/ld_ram.lds -nostdlib
# cpu arch
TARGET_ARCH = -mcpu=cortex-m4
# GDB
GDB      = ${PREFIX}-gdb

.PHONY: all clean build debug connect

# sources
C_SRC   := $(wildcard src/*.c)
ASM_SRC := $(wildcard src/*.s)

# build folder
BUILD := build

# put objects into build/
OBJ := $(patsubst src/%.c,$(BUILD)/%.o,$(C_SRC)) \
       $(patsubst src/%.s,$(BUILD)/%.o,$(ASM_SRC))

all: $(BUILD) $(BUILD)/main.elf

# creates build folder
$(BUILD):
	mkdir -p $(BUILD)

# explicit compile rules (don't rely on implicit rules that may miss src paths)
$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $< -o $@

$(BUILD)/%.o: src/%.s | $(BUILD)
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $< -o $@

# link
${BUILD}/main.elf: $(OBJ)
	$(CC) $(TARGET_ARCH) $(LDFLAGS) $(OBJ) -o $@

# remove all build artifacts
clean:
	rm -rf build

# debug infrastructure
connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhosstOnly

debug:
	${GDB} -x debug/stm32-4se.gdb
