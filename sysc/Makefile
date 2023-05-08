TARGET = programm_c
SRC = $(wildcard *.c)


#riscv64-unknown-elf-gcc -g -ffreestanding -O0 -Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,link.ld  array.S -o array

RISCV_GCC_OPTS ?= -g  -mcmodel=medany -ffreestanding -O0 -Wl,--gc-sections
RISCV_LINK_OPTS ?= -static -nostartfiles -lm  -lgcc -T link.ld

$(TARGET) : $(SRC) 
	riscv64-unknown-elf-gcc $(RISCV_GCC_OPTS) -o $@ $(SRC) $(RISCV_LINK_OPTS) crt.S

clean : 
	rm $(TARGET)


