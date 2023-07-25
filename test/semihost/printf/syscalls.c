#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <sys/signal.h>

#include "syscalls.h"

#define EBREAK_OPCODE   0x00100073
#define EBREAK_MCAUSE   0x00000003 //342

#define SLLI_X0_X0_0X1F_OPCODE  0x01f01013
#define SRAI_X0_X0_0X07_OPCODE  0x40705013

#define RISCV_SEMIHOSTING_CALL_NUMBER 7
#define SEMIHOSTING_SYS_WRITE 0x05
#define SEMIHOSTING_SYS_WRITE0 0x04


void trap(uintptr_t mcause, uintptr_t mepc, uintptr_t mtval)
{

    if (mcause == EBREAK_MCAUSE && mtval == EBREAK_OPCODE)
    {
        

        int aligned = ((mepc-4) & 0x0f) == 0;

        if (aligned 
            && *(uint32_t *)mepc     == EBREAK_OPCODE 
            && *(uint32_t *)(mepc-4) == SLLI_X0_X0_0X1F_OPCODE
            && *(uint32_t *)(mepc+4) == SRAI_X0_X0_0X07_OPCODE)
        {
           asm volatile(
            "csrr t0, mepc\n"
            "addi t0, t0, 4\n"
            "csrw mepc, t0\n"
           );
            return;
        }
      
        while(1);
    }

    while(1);
}

static inline int __attribute__ ((always_inline)) call_host(int reason, void* arg) {
 register uintptr_t r0 asm("a0") = reason;
    register uintptr_t r1 asm("a1") = arg;

    asm volatile(
        " .balign 16 \n"
        " .option push \n"
        " .option norvc \n"
        " slli x0, x0, 0x1f \n"
        " ebreak \n"
        " srai x0, x0, 0x7\n"
        " .option pop \n"

                 : "=r"(r0)         /* Outputs */
                 : "r"(r0), "r"(r1) /* Inputs */
                 : "memory");
    return r0;
}


void sh_print(char* str){

call_host(SEMIHOSTING_SYS_WRITE0, (void*) str);

}