```c
#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];// max buffer size

void//VOID!
cat(int fd)// cat func
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {//write buf to fd1 - stdout
      fprintf(2, "cat: write error\n");// output bytes to stderr
      exit(1);
    }
  }
  if(n < 0){
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int // POSIX: int 
main(int argc, char *argv[])//POSIX: int argc —— number of args, char *argv[] —— array of args
{
  int fd, i;

  if(argc <= 1){// no arg in shell
    cat(0);//fd0 shell/keyboard
    exit(0);
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], O_RDONLY)) < 0){// open file by readonly flag, get fd
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
    cat(fd);//fd3
    close(fd);//Release fd3, in next loop, open syscall return fd3 again and close again...
  }
  exit(0);
}

```
I add a debug code in cat.c line 39
```c
printf("fd = %d\n", fd); // so, what's this fd number?
```
In xv6
```bash
cat hello world
fd = 3
hello
fd = 3
world
```