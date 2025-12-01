```c

// open.c create a file, write to it.

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int fd = open("output.txt", O_WRONLY | O_CREATE);
  write(fd, "ooo\n", 4);

  exit(0);
}

```

open.c create a file and write some text in it.

in line 11, use the syscall `open`
- arg1 = the file name
- arg2 = `O_flag` tell kernel the way to exec open syscall
  - `O_WRONLY` open for write only
  - `O_CREATE` create if not exist

open.c return a number: fd

write the fd number with data

fd actually indexing into a table inside the kernel

kernel maintains state for each process with the table

#### Critical point:
- Same fd number ≠ same file.
- Each process has its own FD table.
```
Process FD = index number only
Kernel  FD = actual file object & state

FD exists per process.
File objects exist in kernel.
```

#### open(): Python vs C
```python
f = open("a.txt", "w")
# Python runtime -> file object -> libC -> sys_open -> kernel
```
```c
int fd = open("a.txt", O_WRONLY | O_CREATE);

user program (open.c)
↓
user/user.h (function declaration)
↓
user/usys.S (syscall stub)
↓
ecall → trap → kernel
↓
kernel/syscall.c  (syscall dispatcher)
↓
sys_open()    ← kerner execution
↓
fs.c → file.c → inode.c
↓
fd returned to user space
```

#### RISC-V ecall
```
User space
  ↓  (ecall instruction)
Trap into kernel
  ↓
Kernel inspects registers (a0–a7) and identifies syscall number
  ↓
Kernel executes corresponding handler (sys_open / sys_read / sys_write / ...)
  ↓
Kernel returns results to user space and restores context
```