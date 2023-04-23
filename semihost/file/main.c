#include <stdio.h>

#include "syscalls.h"

//extern void initialise_monitor_handles(void);

int main(){
    //initialise_monitor_handles();
    //printf("OOOOOOHhhh!\n");
asm volatile(
    "addi t0, zero, 4\n"
    "slli x0, x0, 0x1f \n"
);
sh_print("Hello, semihosting!!!\n");

}