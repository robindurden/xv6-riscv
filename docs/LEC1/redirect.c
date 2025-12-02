
#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

// redirect.c: run a command with output redirected

int
main()
{
  int pid;

  pid = fork();
  if (pid == 0) {                            // child
    close(1);                                // Release open file fd
    open("output.txt", O_WRONLY | O_CREATE); // returns an fd

    char *argv[] = {"echo", "this", "is", "rediredctd", "echo", 0};
    exec("echo", argv);
    printf("exec failed\n");
    exit(1);
  } else {
    wait((int *)0);
  }

  exit(0);
}
/**
 * parent used fd1 to connected to the console
 * child closed fd1, preseved fd0 to connected to the console
 * open is guaranteed to return 1
 * exec echo writes output to fd1
 */