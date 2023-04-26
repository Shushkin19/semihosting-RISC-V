#include <stdio.h>
#include "syscalls.h"

#define SEMIHOSTING_SYS_FILE_MODE_WPLUS 6
#define SEMIHOSTING_SYS_FILE_MODE_RPUS  2
int main(){

    int file_handler_for_write;
    
    if( ( file_handler_for_write=sh_fopen("//home//ubuntu//code//risc-v//one//semihost//file//write.txt", SEMIHOSTING_SYS_FILE_MODE_WPLUS) ) == -1 ) {
    
    sh_print("Cannot open file.\n");
    
    } 
    
    else {
        
        sh_fwrite(file_handler_for_write,"Hello RISC-V\n");

    }
    sh_fclose(file_handler_for_write);


    int file_handler;
    
    if( ( file_handler=sh_fopen("//home//ubuntu//code//risc-v//one//semihost//file//read.txt", SEMIHOSTING_SYS_FILE_MODE_RPUS) ) == -1 ) {
    
    sh_print("Cannot open file.\n");
    
    } 
    else {
       int len = sh_flen(file_handler);
        char str[24];
        int state = sh_fseek(file_handler, 0);
        int read_byte = sh_fread(file_handler,&str,len);
       sh_print(str);
    }

    sh_fclose(file_handler);



    return 0;
}