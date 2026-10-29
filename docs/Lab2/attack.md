我认为此题为达到通过目的 是可以不择手段的


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

exit()
 ├─ uvmfree(p->pagetable, p->sz)
 │   ├─ free user page（PTE -> phy page）
 │   └─ free pagetable page（pahetable self）
 └─ freepagetable()

kwait
freeproc
kfree(pa)
    memset(pa, 1, PGSIZE);// Fill 1 to catch dangling refs.
    pa -> freelist
attack
    kalloc
    
```

```
freelist is LIFO
```