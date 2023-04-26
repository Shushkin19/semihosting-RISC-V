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

//console io
#define SEMIHOSTING_SYS_WRITE0 0x04

//file
#define SEMIHOSTING_SYS_WRITE 0x05
#define SEMIHOSTING_SYS_OPEN  0x01
#define SEMIHOSTING_SYS_READ  0x06
#define SEMIHOSTING_SYS_CLOSE 0x02
#define SEMIHOSTING_SYS_FLEN  0x0C

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



int my_strlen(const char* str){
    int count = 0;
    while(str[count]!='\0'){
        count++;
    }

    return count;
}


void sh_print(char* str){

call_host(SEMIHOSTING_SYS_WRITE0, (void*) str);

}

int sh_fopen(const char *fname, int mode){
    uintptr_t arg[3];
	arg[0] = (uintptr_t)fname;
	arg[1] = (uintptr_t)mode;
	arg[2] = (uintptr_t)my_strlen(fname);

	int file_handle = call_host(SEMIHOSTING_SYS_OPEN, (void *)arg);
	return file_handle;
}

int sh_fclose(int file_handler){

    int result = call_host(SEMIHOSTING_SYS_CLOSE, file_handler);
    
    return result;
}

int sh_fwrite(int file_handler, const char *str){
    //implemented only for char*
    uintptr_t arg[3];
    arg[0] = (uintptr_t) file_handler;
    arg[1] = (uintptr_t) str;
    arg[2] = (uintptr_t) my_strlen(str);
    return call_host(SEMIHOSTING_SYS_WRITE, (void*)arg);


}

int sh_fread(int file_handler, const char* str, int len){

    uintptr_t arg[1];
    arg[0] = (uintptr_t) file_handler;
    arg[1] = (uintptr_t) str;
    arg[2] = (uintptr_t) len;
    return call_host(SEMIHOSTING_SYS_READ, (void*)arg);


}


int sh_flen(int file_handler)  {

    uintptr_t arg[1];
    arg[0] = (uintptr_t) file_handler;
    return call_host(SEMIHOSTING_SYS_FLEN, (void*)arg);

}