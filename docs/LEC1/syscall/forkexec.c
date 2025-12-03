
#include "kernel/types.h"
#include "user/user.h"

// forkexec.c: fork then exec

int
main()
{
  int pid, status;

  pid = fork();
  if (pid == 0) { // child
    char *argv[] = {"echo", "THIS", "IS", "ECHO", 0};
    exec("echo", argv); // echo exit(0)
    printf("exec failed\n");
    exit(1); // address the status to kernel
  } else {   // parent
    printf("parent waiting\n");
    wait(&status); // 0/1
    printf("the child exited with status %d\n", status);
  }

  exit(0);
}

/*
Note:
copy of fork , memory is wasted: copyed memory dropped and replaced with exec
So, I need to do some optimizations later:
- virtual memory
- lazy copy
*/