```c
// copy.c: copy input to output

#include "kernel/types.h"
#include "user/user.h"

int main()
{

    char buf[64];
    while (1)
    {
        int n = read(0, buf, sizeof(buf));// read syscall
        if (n <= 0)
            break;
        write(1, buf, n);
    }

    exit(0);
}
```
This code used 3 syscalls: read, write, and exit.
- read: it takes 3 arguments:
    - fd 0: file descriptor —— it refers to a previously opened file. shell ensures when program starts,default it's fd 0 connected to shell input. fd 1 connected to shell output, fd 0&1 is the unix default order.
    - buf: a pointer to memory needed to read, In line 10, already allocated 64 bytes on stack for read.
    - maximum size to read
In this code not checkout error, in read work should be carefully.

OS just process 8-bit stream

If file cotains millions of bytes, need cyle read calls(64 bytes once), like a stream.