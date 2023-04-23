

.equ REGBYTES, 4


.equ MSTATUS_MPP, 0x00001800


  .section ".text.init"
  .globl _start
_start:
  li  x1, 0
  li  x2, 0
  li  x3, 0
  li  x4, 0
  li  x5, 0
  li  x6, 0
  li  x7, 0
  li  x8, 0
  li  x9, 0
  li  x10,0
  li  x11,0
  li  x12,0
  li  x13,0
  li  x14,0
  li  x15,0
  li  x16,0
  li  x17,0
  li  x18,0
  li  x19,0
  li  x20,0
  li  x21,0
  li  x22,0
  li  x23,0
  li  x24,0
  li  x25,0
  li  x26,0
  li  x27,0
  li  x28,0
  li  x29,0
  li  x30,0
  li  x31,0

  # initialize trap vector
  la t0, trap_entry
  csrw mtvec, t0

.option push
.option norelax
  la gp, __global_pointer$
.option pop

  la  tp, _end + 63
  and tp, tp, -64

  
  csrr a0, mhartid
  li a1, 1
1:bgeu a0, a1, 1b

  # give each core 128KB of stack + TLS
.equ STKSHIFT, 17
  add sp, a0, 1
  sll sp, sp, STKSHIFT
  add sp, sp, tp
  sll a2, a0, STKSHIFT
  add tp, tp, a2

  j main

  .align 2
trap_entry:
  addi sp, sp, -272

 sw x1, 1*REGBYTES(sp)
  sw x2, 2*REGBYTES(sp)
  sw x3, 3*REGBYTES(sp)
  sw x4, 4*REGBYTES(sp)
  sw x5, 5*REGBYTES(sp)
  sw x6, 6*REGBYTES(sp)
  sw x7, 7*REGBYTES(sp)
  sw x8, 8*REGBYTES(sp)
  sw x9, 9*REGBYTES(sp)
  sw x10, 10*REGBYTES(sp)
  sw x11, 11*REGBYTES(sp)
  sw x12, 12*REGBYTES(sp)
  sw x13, 13*REGBYTES(sp)
  sw x14, 14*REGBYTES(sp)
  sw x15, 15*REGBYTES(sp)
  sw x16, 16*REGBYTES(sp)
  sw x17, 17*REGBYTES(sp)
  sw x18, 18*REGBYTES(sp)
  sw x19, 19*REGBYTES(sp)
  sw x20, 20*REGBYTES(sp)
  sw x21, 21*REGBYTES(sp)
  sw x22, 22*REGBYTES(sp)
  sw x23, 23*REGBYTES(sp)
  sw x24, 24*REGBYTES(sp)
  sw x25, 25*REGBYTES(sp)
  sw x26, 26*REGBYTES(sp)
  sw x27, 27*REGBYTES(sp)
  sw x28, 28*REGBYTES(sp)
  sw x29, 29*REGBYTES(sp)
  sw x30, 30*REGBYTES(sp)
  sw x31, 31*REGBYTES(sp)

  csrr a0, mcause
  csrr a1, mepc
  csrr a2, mtval
  #mv a2, sp
  jal trap
  csrw mepc, a0

  # Remain in M-mode after eret
  li t0, MSTATUS_MPP
  csrs mstatus, t0

  lw x1, 1*REGBYTES(sp)
  lw x2, 2*REGBYTES(sp)
  lw x3, 3*REGBYTES(sp)
  lw x4, 4*REGBYTES(sp)
  lw x5, 5*REGBYTES(sp)
  lw x6, 6*REGBYTES(sp)
  lw x7, 7*REGBYTES(sp)
  lw x8, 8*REGBYTES(sp)
  lw x9, 9*REGBYTES(sp)
  lw x10, 10*REGBYTES(sp)
  lw x11, 11*REGBYTES(sp)
  lw x12, 12*REGBYTES(sp)
  lw x13, 13*REGBYTES(sp)
  lw x14, 14*REGBYTES(sp)
  lw x15, 15*REGBYTES(sp)
  lw x16, 16*REGBYTES(sp)
  lw x17, 17*REGBYTES(sp)
  lw x18, 18*REGBYTES(sp)
  lw x19, 19*REGBYTES(sp)
  lw x20, 20*REGBYTES(sp)
  lw x21, 21*REGBYTES(sp)
  lw x22, 22*REGBYTES(sp)
  lw x23, 23*REGBYTES(sp)
  lw x24, 24*REGBYTES(sp)
  lw x25, 25*REGBYTES(sp)
  lw x26, 26*REGBYTES(sp)
  lw x27, 27*REGBYTES(sp)
  lw x28, 28*REGBYTES(sp)
  lw x29, 29*REGBYTES(sp)
  lw x30, 30*REGBYTES(sp)
  lw x31, 31*REGBYTES(sp)

  addi sp, sp, 272
  mret

.section ".tohost","aw",@progbits
.align 6
.globl tohost
tohost: .dword 0
.align 6
.globl fromhost
fromhost: .dword 0
