# POSIX
POSIX (Portable Operating System Interface) is a family of standards specified by the IEEE for maintaining compatibility between operating systems. POSIX defines the application programming interface (API), along with command line shells and utility interfaces, for software compatibility with variants of Unix and other operating systems.
## Program Arguments
main(argc, argv) is the POSIX standard provided interface for program accepting command-line arguments.
#### Why argc/argv?
- argc = argument count
- argv = argument vector
#### argc/argv's structure:
- argv[0] = name of the program
- argv[1] = first argument
- argv[2] = second argument
- ...
- argv[argc] = NULL
#### int main()
- main return int is the process's exit code
- return code saved by kernel, taken by parent process
#### Example:
```c
cat a.c b.txt
```
then:
```
argc = 3
argv[0] = "cat"
argv[1] = "a.c"
argv[2] = "b.txt"
argv[3] = NULL
```
## File Descriptors
Every process have 3 fd when it started
- fd0 STDIN  shell/keyboard
- fd1 STDOUT terminal
- fd2 STDERR terminal

when the process used open syscall to open other file:
- fd3 opened file
- fd4 another opened file
......
## EOF
end-of-file
Ctrl-D = ASCII 0x04
In shell - sh.c
```c
getcmd()
...
if(buf[0] == 0) // EOF
    return -1;
```