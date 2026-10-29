## VM
- VA: Virtual Address
- PA: Physical Address
- MMU: HW splits VA into VPN and Offset
- VPN: Virtual page number
- PPN: Physical page number
- TLB: Translation Lookaside Buffer
- page size: = 4 KB = 4096 bytes = 2¹²
- Offset: 12bits, 0x123(2^3 in hex,range 0-4095)

### e.g.
#### Translation
```
VA = 0x00001234
Offset = 0x234   (lower 12 bits)
VPN    = 0x00001
VPN 0x00001 -> PPN 0x0ABC
PA     =  0x0ABC234
```

#### In program
```
VA:
0x1000 ~ 0x1FFF   (page 0)
0x2000 ~ 0x2FFF   (page 1)
0x3000 ~ 0x3FFF   (page 2)

PA:
page 0 -> DRAM frame No.500
page 1 -> DRAM frame No.12
page 2 -> DRAM frame No.901
```


### ASCII Img
```text
Virtual Address Translation (4KB pages => 12-bit offset)

(1) CPU issues a *virtual* address (VA)
    VA:  |-------- VPN --------|-- Offset --|
         |     (virtual page)  | (12 bits)  |
         +---------------------+------------+

(2) MMU splits VA into VPN and Offset
                 VPN ----------------------+
                                            \
(3) TLB lookup (cache of recent VPN->PPN)    \
    +-------------------+                     \
    |       TLB         |                      \
    |  VPN -> PPN,perm  |                       \
    +-------------------+                        \
          | hit                                   | miss
          v                                       v
      (use PPN)                           (4) Page Table Walk
                                              Page table lives in DRAM
                                              PTBR/SATP points to root
                                              +----------------------+
                                              |   Page Table (DRAM)  |
                                              |  [VPN] -> PTE        |
                                              +----------+-----------+
                                                         |
(5) Fetch PTE from DRAM                                   v
    PTE contains: [ PPN | flags ]                   PTE: [PPN | flags]

(6) Check flags (valid? R/W/X? user?)
    - invalid -> page fault
    - permission fail -> trap

(7) Form *physical* address (PA) by combining:
    PA = (PPN << 12) | Offset

    Physical Address:
    PA:  |-------- PPN --------|-- Offset --|
         |   (physical page)   | (same 12)  |
         +---------------------+------------+

(8) Access DRAM at PA
    DRAM[PA]  -> load/store completes

```