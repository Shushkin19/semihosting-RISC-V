#include <stdint.h>

#define SYS_exit 93
#define SYS_exit_group 94
#define SYS_getpid 172
#define SYS_kill 129
#define SYS_tgkill 131
#define SYS_read 63
#define SYS_write 64
#define SYS_openat 56
#define SYS_close 57
#define SYS_lseek 62
#define SYS_brk 214
#define SYS_linkat 37
#define SYS_unlinkat 35
#define SYS_mkdirat 34
#define SYS_renameat 38
#define SYS_chdir 49
#define SYS_getcwd 17
#define SYS_fstat 80
#define SYS_fstatat 79
#define SYS_faccessat 48
#define SYS_pread 67
#define SYS_pwrite 68
#define SYS_uname 160
#define SYS_getuid 174
#define SYS_geteuid 175
#define SYS_getgid 176
#define SYS_getegid 177
#define SYS_gettid 178
#define SYS_sysinfo 179
#define SYS_mmap 222
#define SYS_munmap 215
#define SYS_mremap 216
#define SYS_mprotect 226
#define SYS_prlimit64 261
#define SYS_getmainvars 2011
#define SYS_rt_sigaction 134
#define SYS_writev 66
#define SYS_gettimeofday 169
#define SYS_times 153
#define SYS_fcntl 25
#define SYS_ftruncate 46
#define SYS_getdents 61
#define SYS_dup 23
#define SYS_dup3 24
#define SYS_readlinkat 78
#define SYS_rt_sigprocmask 135
#define SYS_ioctl 29
#define SYS_getrlimit 163
#define SYS_setrlimit 164
#define SYS_getrusage 165
#define SYS_clock_gettime 113
#define SYS_set_tid_address 96
#define SYS_set_robust_list 99
#define SYS_madvise 233
#define SYS_statx 291

#define OLD_SYSCALL_THRESHOLD 1024
#define SYS_open 1024
#define SYS_link 1025
#define SYS_unlink 1026
#define SYS_mkdir 1030
#define SYS_access 1033
#define SYS_stat 1038
#define SYS_lstat 1039
#define SYS_time 1062

#define SEMIHOSTING_SYS_CLOSE 0x02
#define SEMIHOSTING_SYS_CLOCK 0x10
#define SEMIHOSTING_SYS_ELAPSED 0x30
#define SEMIHOSTING_SYS_ERRNO 0x13
#define SEMIHOSTING_SYS_EXIT 0x18
#define SEMIHOSTING_SYS_EXIT_EXTENDED 0x20
#define SEMIHOSTING_SYS_FLEN 0x0C
#define SEMIHOSTING_SYS_GET_CMDLINE 0x15
#define SEMIHOSTING_SYS_HEAPINFO 0x16
#define SEMIHOSTING_SYS_ISERROR 0x08
#define SEMIHOSTING_SYS_ISTTY 0x09
#define SEMIHOSTING_SYS_OPEN 0x01
#define SEMIHOSTING_SYS_READ 0x06
#define SEMIHOSTING_SYS_READC 0x07
#define SEMIHOSTING_SYS_REMOVE 0x0E
#define SEMIHOSTING_SYS_RENAME 0x0F
#define SEMIHOSTING_SYS_SEEK 0x0A
#define SEMIHOSTING_SYS_SYSTEM 0x12
#define SEMIHOSTING_SYS_TICKFREQ 0x31
#define SEMIHOSTING_SYS_TIME 0x11
#define SEMIHOSTING_SYS_TMPNAM 0x0D
#define SEMIHOSTING_SYS_WRITE 0x05
#define SEMIHOSTING_SYS_WRITEC 0x03
#define SEMIHOSTING_SYS_WRITE0 0x04
#define SEMIHOSTING_USER_CMD_0X100 0x100 /* First user cmd op code */
#define SEMIHOSTING_USER_CMD_0X107 0x107 /* Last supported user cmd op code */
#define SEMIHOSTING_USER_CMD_0X1FF 0x1FF /* Last user cmd op code */

#define EBREAK_OPCODE 0x00100073
#define EBREAK_MCAUSE 0x00000003 // 342
#define SLLI_X0_X0_0X1F_OPCODE 0x01f01013
#define SRAI_X0_X0_0X07_OPCODE 0x40705013
#define RISCV_SEMIHOSTING_CALL_NUMBER 7

int sh_fopen(const char *fname, int mode, int lenght);

int sh_print(char *str);

int sh_fclose(int file_handler);

int sh_fwrite(int file_handler, const char *str, int lenght);

int sh_fread(int file_handler, char *str, int len);

int sh_flen(int file_handler);

int sh_fseek(int file_handler, long position);

#include <sys/timespec.h>

struct kernel_stat
{
    unsigned long long st_dev;
    unsigned long long st_ino;
    unsigned int st_mode;
    unsigned int st_nlink;
    unsigned int st_uid;
    unsigned int st_gid;
    unsigned long long st_rdev;
    unsigned long long __pad1;
    long long st_size;
    int st_blksize;
    int __pad2;
    long long st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    int __glibc_reserved[2];
};
