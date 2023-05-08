#include <stdint.h>

void trap(uintptr_t mcause, uintptr_t mepc,uintptr_t mtval);


void sh_print(char* str);

int sh_fopen(const char *fname, int mode);

int sh_fclose(int file_handler);

int sh_fwrite(int file_handler, const char *str);

int sh_fread(int file_handler,  char* str, int len);

int sh_flen(int file_handler);

int sh_fseek(int file_handler, int byte_offset);