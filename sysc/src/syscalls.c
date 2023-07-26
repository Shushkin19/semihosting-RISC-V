#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <sys/signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/reent.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include "syscalls.h"
#include "../inc/encoding.h"

#if __NEWLIB__ <= 2 && __NEWLIB_MINOR__ <= 5
#define _sbrk sbrk
#endif

struct heapinfo
{
    void *heap_base;
    void *heap_limit;
    void *stack_base;
    void *stack_limit;
};

void mepc_increase()
{
    asm volatile(
        "csrr t0, mepc\n"
        "addi t0, t0, 4\n"
        "csrw mepc, t0\n");
}

extern char __heap_start[];
extern char __heap_end[];
static char *brk = &__heap_start[0];

/* - brk устанавливает конец сегмента данных в значение, указанное в аргументе end_data_segment, когда это значение является приемлимым,
 система симулирует нехватку памяти и процесс не достигает своего максимально возможного размера сегмента данных
- sbrk увеличивает пространство данных программы на increment байт. sbrk не является системным вызовом, он просто является обёрткой (wrapper),
которую использует библиотека C. Вызов sbrk с инкрементом 0 может быть использован, чтобы найти текущее местоположения прерывания программы.

--ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ
В случае успеха brk возвращает ноль, а sbrk возвращает указатель на начало новой области.
 В случае ошибки возвращается -1 is и значение errno устанавливается в ENOMEM.

*/
int _brk(void *addr) /*unused!*/
{
    brk = addr;
    return 0;
}

void *_sbrk(ptrdiff_t incr)
{
    char *old_brk = brk;

    if (__heap_start == __heap_end)
    {
        return NULL;
    }

    if ((brk += incr) < __heap_end)
    {
        brk += incr;
    }
    else
    {
        brk = __heap_end;
    }
    return old_brk;
}

int my_fstat(uintptr_t fd, struct kernel_stat *kst)
{
    if (fd == 1 || fd == 0)
    {
        return 0;
    }

    else if (fd > 1)
    {
        kst->st_uid = fd;
        return 0;
    }

    else
    {
        return fd;
    }
}

int my_write(uintptr_t fd, const char *ptr, uintptr_t len)
{
    return sh_fwrite(fd, ptr, len);
}

int my_open(const char *path, int oflag, ...)
{
    // It is an error to open a file that already exists.
    if ((oflag & O_CREAT) && (oflag & O_EXCL))
    {
        struct stat st;
        int res;
        res = stat(path, &st);
        if (res != -1)
        {
            printf("error _open\n");
            return -1;
        }
    }

    int aflags = 0;
    // The flags are Unix-style, so we need to convert them.
#ifdef O_BINARY
    if (oflag & O_BINARY)
    {
        aflags |= 1;
    }
#endif

    // In O_RDONLY we expect aflags == 0.

    if (oflag & O_RDWR)
    {
        aflags |= 2;
    }

    if ((oflag & O_CREAT) || (oflag & O_TRUNC) || (oflag & O_WRONLY))
    {
        aflags |= 4;
    }

    if (oflag & O_APPEND)
    {
        // Can't ask for w AND a; means just 'a'.
        aflags &= ~4;
        aflags |= 8;
    }

    return sh_fopen(path, aflags, strlen(path));
}

int my_fseek(uintptr_t fd, int byte_offset, int origin)
{
    if (origin == 2)
    {
        int size = sh_flen(fd);
        sh_fseek(fd, size - 1);
        return size;
    }
    else if (origin == 0)
    {

        return sh_fseek(fd, 0);
    }
}
/*Когда старший бит регистра mcause равен 1, тип прерывания — прерывание. Код исключения в регистре mcause читается.
Если код исключения равен 7, это прерывание по таймеру. В этом случае вызывается обработчик прерывания таймера.
Если код исключения равен 3, это программное прерывание. В этом случае вызывается программный обработчик прерывания.
Когда старший бит регистра mcause равен 0, тип прерывания — исключение или системный вызов. Код исключения в регистре mcause читается.
Если код исключения равен 2, 4 или 6, это исключение, и вызывается соответствующий обработчик исключения.
Если код исключения 9 или 11, это системный вызов, и вызывается обработчик ecall.*/
uintptr_t __attribute__((weak)) ecall_handle_trap(uintptr_t a7, uintptr_t a0, uintptr_t a1, uintptr_t a2,
                                                  uintptr_t a3, uintptr_t a4, uintptr_t a5)
{

    mepc_increase();
    asm volatile(
        "li t1, 2048\n"
        "csrw medeleg, t1\n");
    int tmp;
    switch (a7)
    {
    case SYS_fstat:
        return my_fstat(a0, a1);
        break;

    case SYS_write:
        return my_write(a0, a1, a2);
        break;

    case SYS_brk:
        return _sbrk(a0);
        break;

    case SYS_open:
        return my_open(a0, a1, a2);
        break;

    case SYS_lseek:
        return my_fseek(a0, a1, a2);
        break;

    case SYS_close:
        return sh_fclose(a0);
        break;

    case SYS_read:
        return sh_fread(a0, a1, a2);
        break;

    default:

        sh_print(a7);
        break;
    }
}

uintptr_t __attribute__((weak)) machine_handle_trap(uintptr_t mcause, uintptr_t mepc, uintptr_t regs[32], uintptr_t mtval)
{
    switch (mcause)
    {

    case CAUSE_BREAKPOINT:

        if (mcause == EBREAK_MCAUSE && mtval == EBREAK_OPCODE)
        {

            int aligned = ((mepc - 4) & 0x0f) == 0;

            if (aligned && *(uint32_t *)mepc == EBREAK_OPCODE && *(uint32_t *)(mepc - 4) == SLLI_X0_X0_0X1F_OPCODE && *(uint32_t *)(mepc + 4) == SRAI_X0_X0_0X07_OPCODE)
            {
                asm volatile(
                    "csrr t0, mepc\n"
                    "addi t0, t0, 4\n"
                    "csrw mepc, t0\n");
                return;
            }

            while (1)
                ;
        }

        break;

    case CAUSE_MACHINE_ECALL:
        return ecall_handle_trap(regs[17], regs[10], regs[11], regs[12], regs[13], regs[14], regs[15]);

        break;

    case CAUSE_SUPERVISOR_ECALL:

        break;

    case CAUSE_USER_ECALL:

        break;

    case CAUSE_STORE_ACCESS:
        sh_print("Store access fault\n");
        while (1)
            ;
        break;

    case CAUSE_FETCH_ACCESS:
        sh_print("Instruction access fault\n");
        while (1)
            ;
        break;

    case CAUSE_MISALIGNED_LOAD:
        sh_print("Load address misaligned");
        while (1)
            ;
    default:
        return;
        sh_print("default\n");
        break;
    }
}

static inline int __attribute__((always_inline)) call_host(int reason, void *arg)
{
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

int my_strlen(const char *str)
{
    int count = 0;
    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}

int sh_print(char *str)
{

    return call_host(SEMIHOSTING_SYS_WRITE0, (void *)str);
}

int sh_fopen(const char *fname, int mode, int lenght)
{
    uintptr_t arg[3];
    arg[0] = (uintptr_t)fname;
    arg[1] = (uintptr_t)mode;
    arg[2] = (uintptr_t)lenght;

    int file_handle = call_host(SEMIHOSTING_SYS_OPEN, (void *)arg);
    return file_handle;
}

int sh_fclose(int file_handler)
{

    int result = call_host(SEMIHOSTING_SYS_CLOSE, file_handler);

    return result;
}

int sh_fwrite(int file_handler, const char *str, int lenght)
{
    // implemented only for char*
    uintptr_t arg[3];
    arg[0] = (uintptr_t)file_handler;
    arg[1] = (uintptr_t)str;
    arg[2] = (uintptr_t)lenght;
    return call_host(SEMIHOSTING_SYS_WRITE, (void *)arg);
}

int sh_fread(int file_handler, char *str, int len)
{

    uintptr_t arg[3];
    arg[0] = (uintptr_t)file_handler;
    arg[1] = (uintptr_t)str;
    arg[2] = (uintptr_t)len;
    return call_host(SEMIHOSTING_SYS_READ, (void *)arg);
}

int sh_flen(int file_handler)
{

    uintptr_t arg[1];
    arg[0] = (uintptr_t)file_handler;
    return call_host(SEMIHOSTING_SYS_FLEN, (void *)arg);
}

int sh_fseek(int file_handler, long position)
{

    uintptr_t arg[2];
    arg[0] = (uintptr_t)file_handler;
    arg[1] = (uintptr_t)position;
    return call_host(SEMIHOSTING_SYS_SEEK, (void *)arg);
}

/*> Вызов полухостинга SYS_HEAPINFO должен возвращать массив
> из четырех гостевых адресов:
> * база кучи памяти
> * ограничение кучи памяти
> * база памяти стека
> * лимит стековой памяти*/
int sh_heapinfo(struct heapinfo *info)
{
    return call_host(SEMIHOSTING_SYS_HEAPINFO, &info);
}