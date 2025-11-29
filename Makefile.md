# Makefile
This file describe the Makefile, to understand how to build the kernel.

## Overview
Makefile is a file,tell ``make`` tool  how to build the project.
Only type ``make`` command in terminal, it will read the Makefile in current directory.

## Command
```bash
make [target] [variable=value]
```
In this Makefile, the default target is `all`, so if you just type `make`, it will build the `all` target.
`quem` is a target in this Makefile, so `make qemu` will build the `qemu` target.
```
make qemu
```
- Ctrl+A → X = QEMU: Terminated
- Ctrl+A → H = QEMU: Help
## Variables
Variable Definition
```makefile
K = kernel
U = user
```
After the definition, you can use `$(K)` to refer to `kernel` and `$(U)` to refer to `user`.

## Object Files
```makefile
OBJS = \
  $K/entry.o \
  $K/start.o \
  ......
```
`OBJS` means OBJect fileS.</br>
`OBJS` defines a set of object files required to link for kernel.
```makefile
OBJS = \
  kernel/entry.o \
  kernel/start.o \
  ...
```
`.o` file also called object file, 
```
source code (.c / .S)
        ↓ compilation
object file (.o)
        ↓ linking
executable (kernel / program)
```

## Tool Prefix
`ifndef` means "if not defined", then do something.
```makefile
ifndef TOOLPREFIX

ifndef VAR
   ... do something ...
endif
```
`TOOLPREFIX` is a variable, use `:=` to assign its value immadiately
`TOOLPREFIX` can be:
- riscv64-unknown-elf-
- riscv64-elf-
- riscv64-linux-gnu-
- iscv64-unknown-linux-gnu-
- not found, exit 1, make terminated

```makefile
TOOLPREFIX := $(shell ...)

- `make` read Makefile
-  Descovery the expression `TOOLPREFIX := $(shell ...)`
-  Run the shell script to check the toolchain prefix
-  Assign the result to `TOOLPREFIX`
```
RISC-V Toolchain install</br>
MacOS: https://github.com/riscv-software-src/homebrew-riscv</br>
After installation, you can print the toolchain prefix.</br>
```bash
riscv64-unknown-elf-objdump -i
riscv64-unknown-elf-gcc --version
make -pn | grep ^TOOLPREFIX
```
Target Triple: `<architecture>-<vendor>-<abi>`
- architecture: riscv64
- vendor: unknown
- abi: elf

ABI = Application Binary Interface
- darwin = MacOS
- gnu = Linux
- win32 = Windows
- elf = Executable and Linkable Format

## Toolchain variables
All toolchain point to RISC-V cross compiler toolchain.
- CC: C Compiler (riscv64-unknown-elf-gcc)
- AS: Assembler (riscv64-unknown-elf-as)
- LD: Linker (riscv64-unknown-elf-ld)
- OBJCOPY: Object Copy (riscv64-unknown-elf-objcopy
- OBJDUMP: Object Dump (riscv64-unknown-elf-objdump)

## CFLAGS
CFLAGS is C Compiler FLAGs, used when compile C source code.
- Compiler logs and optimization
    - `-Wall` Warnings All
    - `-O` Optimization
    - ......
- Architecture specific
    - `-march` Machine Architecture
    - `rv64gc` RISC-V 64-bit, General extensions + Compressed extensions
- Core flags
    - `-ffreestanding` Freestanding environment
    - `-nostdlib` No standard library
    - `-fno-common` Forces strict global variable definition
    - `-fno-builtin` No built-in functions, must implement by yourself

Thoose CFLAGS force the developer must write everything from a white paper.

## Disable PIE
PIE = Position Independent Executable</br>
PIE allows program loaded at random address in memory.</br>
Kernel must be loaded at a fixed address, so disable PIE.

## LDFLAGS
LDFLAGS is Linker FLAGs, used when link object files to executable.</br>
`-z max-page-size=4096`</br>
xv6 kernel use 4KB page size, so set linker maximum page size to 4096 bytes (4KB).</br>

## kernel/kernel
kernel/kernel is the final executable file of the kernel.</br>
- The linking process will combine all object files(.o) in `OBJS` into `kernel/kernel`.
- Output assembly code of the kernel `kernel/kernel.asm`.
- Output symbol table for user and tools  `kernel/kernel.sym`.

## User Library and Programs
ULIB is a mini user-time library
- ulib.o : user library object file
- usys.o : user system call object file
- printf.o : user printf object file
- umalloc.o : user malloc/free object file

$U/usys.S : $U/usys.pl
means that usys.S is not written manually,
it is generated from usys.pl at build time,
creating assembly stubs for system calls,
enabling user programs to invoke kernel functions via ecall.

UPROGS is user programs

`fs.img` is the file system image

## QEMUOPTS
QEMUOPTS are options for QEMU emulator when run the kernel.</br>
- `-machine virt`: RISC-V virtual machine
- `-kernel kernel/kernel`
- `-drive file=fs.img`
- `-nographic` no UI, in terminal
- `-smp 3` multi-core

## make qemu
`make qemu` will build the kernel and run it in QEMU emulator.
```
check qemu version
    ↓
compil kernel
    ↓
package fs.img
    ↓
run qemu with QEMUOPTS
```