### Reading data struces:
	•	user/user.ld
	•	kernel/memlayout.h
	•	kernel/vm.c

	•	kernel/proc.h
	•	kernel/file.h
	•	kernel/buf.h

	•	kernel/param.h
	•	kernel/fs.h
	•	kernel/sysfile.c

	•	kernel/syscall.c
	•	kernel/exec.c
	•	kernel/string.c

	•	kernel/kalloc.c
	•	kernel/bio.c

```bash
robin@mbp xv6-riscv master % riscv64-unknown-elf-objdump -f user/_cat

user/_cat:     file format elf64-littleriscv
architecture: riscv:rv64, flags 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
start address 0x00000000000000f6


robin@mbp xv6-riscv master % riscv64-unknown-elf-nm -n user/_cat 
0000000000000000 T cat
000000000000007e T main
00000000000000f6 T start
0000000000000106 T strcpy
0000000000000126 T strcmp
0000000000000156 T strlen
0000000000000182 T memset
00000000000001a8 T strchr
00000000000001d0 T gets
0000000000000246 T stat
0000000000000282 T atoi
00000000000002ce T memmove
000000000000032a T memcmp
0000000000000364 T memcpy
0000000000000378 T sbrk
000000000000038e T sbrklazy
00000000000003a4 T fork
00000000000003ac T exit
00000000000003b4 T wait
00000000000003bc T pipe
00000000000003c4 T read
00000000000003cc T write
00000000000003d4 T close
00000000000003dc T kill
00000000000003e4 T exec
00000000000003ec T open
00000000000003f4 T mknod
00000000000003fc T unlink
0000000000000404 T fstat
000000000000040c T link
0000000000000414 T mkdir
000000000000041c T chdir
0000000000000424 T dup
000000000000042c T getpid
0000000000000434 T sys_sbrk
000000000000043c T pause
0000000000000444 T uptime
000000000000044c t putc
000000000000046a t printint
0000000000000508 T vprintf
00000000000007c8 T fprintf
00000000000007f2 T printf
0000000000000824 T free
00000000000008aa T malloc
00000000000009f0 r digits
0000000000001000 b freep
0000000000001010 B buf
0000000000001210 b base
```
How C programs are loaded by the kernel?


### User space vuirtual memory layout

```text
0x00000000
│
│  .text        ← instructions read-only
│
│  .rodata      ← Read-Only Data
│
│  .data        ← global variables initialized
│  .bss         ← global variables uninitialized
│
│  heap         ← sbrk() grows upward
│
│  ...          ← void space
│
│  stack        ← grows downward (argv / argc in here)
│
│  trapframe    ← userspace not writable
│  trampoline   ← userspace not executable
│
MAXVA
```

### start->main->exit trace
```text
exec()
 └── user/_cat loaded into memory
     └── start(argc, argv)   ← ELF entry point
         └── main(argc, argv)
             └── return r
         └── exit(r)         ← ensure process termination
```
- start is ABI glue
- exit must be called

### danging pointers
```c
char *p = malloc(100);
free(p);
// p is now a dangling pointer
p[0]='a'; // silent corruption
```

### argv in stack
```c
int main(int argc, char *argv[])
```

```text
high address
│
│  "file2\0"
│  "file1\0"
│
│  argv[2] ──┐
│  argv[1] ──┼─→ points to strings above
│  argv[0] ──┘
│
│  argc
│
low address
```

### string
string maybe cross page
```text
| valid page | unvalid page |
"hello\0" 's' '\0' in next page
```

Kernel used copyinstr to safely copy string from user to kernel
```c
copyinstr(pagetable, dst, user_src, max);
```
- copy by bytes
- checkout pagetable
- ensure '\0'
- limit max length