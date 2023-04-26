#include <stdio.h>
#include "syscalls.h"

#define SEMIHOSTING_SYS_FILE_MODE_WRITE 6

int main(){
    int file_handler_for_write;
    
    if( ( file_handler_for_write=sh_fopen("//home//ubuntu//code//risc-v//one//semihost//file//write.txt", SEMIHOSTING_SYS_FILE_MODE_WRITE) ) == -1 ) {
    
    sh_print("Cannot open file.\n");
    
    } 
    
    else {
        
        sh_fwrite(file_handler_for_write,"Hello RISC-V\n");

    }
    sh_fclose(file_handler_for_write);


    return 0;
}