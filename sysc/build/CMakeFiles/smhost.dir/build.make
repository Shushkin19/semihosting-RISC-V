# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build

# Include any dependencies generated for this target.
include CMakeFiles/smhost.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/smhost.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/smhost.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/smhost.dir/flags.make

CMakeFiles/smhost.dir/src/main.c.o: CMakeFiles/smhost.dir/flags.make
CMakeFiles/smhost.dir/src/main.c.o: ../src/main.c
CMakeFiles/smhost.dir/src/main.c.o: CMakeFiles/smhost.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/smhost.dir/src/main.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/smhost.dir/src/main.c.o -MF CMakeFiles/smhost.dir/src/main.c.o.d -o CMakeFiles/smhost.dir/src/main.c.o -c /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/src/main.c

CMakeFiles/smhost.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/smhost.dir/src/main.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/src/main.c > CMakeFiles/smhost.dir/src/main.c.i

CMakeFiles/smhost.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/smhost.dir/src/main.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/src/main.c -o CMakeFiles/smhost.dir/src/main.c.s

CMakeFiles/smhost.dir/src/syscalls.c.o: CMakeFiles/smhost.dir/flags.make
CMakeFiles/smhost.dir/src/syscalls.c.o: ../src/syscalls.c
CMakeFiles/smhost.dir/src/syscalls.c.o: CMakeFiles/smhost.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/smhost.dir/src/syscalls.c.o"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/smhost.dir/src/syscalls.c.o -MF CMakeFiles/smhost.dir/src/syscalls.c.o.d -o CMakeFiles/smhost.dir/src/syscalls.c.o -c /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/src/syscalls.c

CMakeFiles/smhost.dir/src/syscalls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/smhost.dir/src/syscalls.c.i"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/src/syscalls.c > CMakeFiles/smhost.dir/src/syscalls.c.i

CMakeFiles/smhost.dir/src/syscalls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/smhost.dir/src/syscalls.c.s"
	riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/src/syscalls.c -o CMakeFiles/smhost.dir/src/syscalls.c.s

# Object files for target smhost
smhost_OBJECTS = \
"CMakeFiles/smhost.dir/src/main.c.o" \
"CMakeFiles/smhost.dir/src/syscalls.c.o"

# External object files for target smhost
smhost_EXTERNAL_OBJECTS =

smhost: CMakeFiles/smhost.dir/src/main.c.o
smhost: CMakeFiles/smhost.dir/src/syscalls.c.o
smhost: CMakeFiles/smhost.dir/build.make
smhost: CMakeFiles/smhost.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable smhost"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smhost.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/smhost.dir/build: smhost
.PHONY : CMakeFiles/smhost.dir/build

CMakeFiles/smhost.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/smhost.dir/cmake_clean.cmake
.PHONY : CMakeFiles/smhost.dir/clean

CMakeFiles/smhost.dir/depend:
	cd /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build /home/shusha/Code/RISC-V/Learn/semihosting-RISC-V/sysc/build/CMakeFiles/smhost.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/smhost.dir/depend

