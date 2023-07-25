cmake_minimum_required(VERSION 3.10)

project(semihosting)

set(LINKER_SCRIPT link.ld)

add_compile_options(-march=rv64imacdf -mabi=ilp64 -mcmodel=medany -g -ffreestanding -O0 -Wl,--gc-sections -static -nostartfiles -lm -lgcc -T $(LINKER_SCRIPT))

add_executable(smhost main.c syscalls.c crt.S)