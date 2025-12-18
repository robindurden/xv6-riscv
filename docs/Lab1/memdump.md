## Memory Dump and Data Types
| Data Type | bytes    |
|----------|---------|
| char| 1   |
| int | 4   |
| long | 8   |
|pointer| 8   |
| uint64| 8   |

When you increment a pointer, it moves by the size of the data type it points to. For example:
```c
int *p;//p = x0 00 00 00 00
p += 1;//1 = sizeof(int) * 1 = x04
```

```
0x80000000

0x80000000: 13 00 00 00
0x80000004: 2a 00 00 00
0x80000008: ff ff ff ff
```
```c
int x = 0x12345678;
unsigned char *p = (unsigned char *)&x;

for (int i = 0; i < sizeof(int); i++) {
    printf("%02x ", p[i]);
}
```
output:
```
78 56 34 12
```
## Pointer
```
addr      value
0x1000    2a
0x1001    00
0x1002    00
0x1003    00
```

```c
char *p = (char *)0x1000;
// p = 0x1000

*(int *)p
read 0x1000..0x1003
→ 0x0000002a
→ 42
2a 00 00 00 → 42
```
