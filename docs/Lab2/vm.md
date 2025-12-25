## MMU（Memory Management Unit）
- Translates Virtual Address (VA) → Physical Address (PA)
- Uses Page Tables and Page Table Entries (PTEs)
- Concatenates Physical Page Number (PPN) with Page Offset
- Page Table Walk
- Uses Translation Lookaside Buffer (TLB) to cach
- Checks PTE permission bits

## OS
### allocate memory
- kalloc: get free physical page *
- kfree(pa): point pa to freelist 
### vm: virtual memory
- pa: physical addresses
- PTE: Page Table Entry 
- va: virtual addresses

```text
page of physical memory
  ↑↓ (kalloc / kfree)
 PTE
  ↑↓ (vm.c)
user virtual addresses
  ↑↓ (copyin / copyout / argstr)
user program
```

```text
typedef uint64 pte_t;
63........10 | 9..8 | 7 6 5 4 3 2 1 0
   PPN        | rsw | D A G U X W R V
```

