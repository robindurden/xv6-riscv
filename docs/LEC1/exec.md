```c
// exec.c: replace a process with an executable file

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  char *argv[] = {"echo", "this", "is", "echo", 0};

  exec("echo", argv);

  printf("exec failed\n");

  exit(0);
}
```
## exec syscall
`exec("echo", argv);`
- OS loading instructions from the file called "echo"
- Replace the current process's memory.
- exec replace itself to echo
- string args: a pointer to memory that contains those bytes
- last arg 0: the end of argv, the last pointer
- 0 or null pointer siginifies the end of the argv array

## important
- exec preserves the current fd table
- orginal exec not return when it replaces to other program
- if exec failed, return -1