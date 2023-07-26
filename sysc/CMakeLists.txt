cmake_minimum_required(VERSION 3.10)

project(semihosting)

# find_program(CMAKE_C_COMPILER riscv64-unknown-elf-gcc)
# find_program(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++)
set(CMAKE_C_COMPILER riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++)
set(LINKER_SCRIPT link.ld)

add_compile_options(-mcmodel=medany -g -ffreestanding -O0 -Wl,--gc-sections -static -nostartfiles -lm -lgcc -T $(LINKER_SCRIPT))

add_executable(smhost src/main.c src/syscalls.c src/crt.S)