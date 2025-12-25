- kernel/sysproc.c
    - uint64 sys_sbrk(void)
- user/ulib.c
    - char * sbrk(int n) 
    - char * sbrklazy(int n)
- return heap end address

- myproc()->sz == 0x4000




```text
sh
    secret xyzzy
    kexit
kwait
freeproc
kfree(pa)
    memset(pa, 1, PGSIZE);// Fill 1 to catch dangling refs.
    pa -> freelist
attack
    kalloc
    
```