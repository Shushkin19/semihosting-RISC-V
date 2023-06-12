#!bin/bash
gnome-terminal -x sh -c "spike --rbb-port=9824 programm_c ; "
gnome-terminal -x sh -c "riscv64-unknown-elf-gdb programm_c -silent; bash"
openocd -f sp.cfg -c "arm semihosting enable"


