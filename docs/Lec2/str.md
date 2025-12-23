```c
#include "kernel/types.h"
#include "user/user.h"

char *s = "123";//readonly data
	
int
main(int ac, char **av)
{
  char s1[4] = {'1', '2', '3', '\0'}; //in stack

  // s and s1 are strings
  printf("s %s s1 %s\n", s, s1);

  // can use index or pointer access
  // s[0]==*(s+0)
  // *s==*(s+0)
  printf("%c %c\n", s[0], *s); 
  printf("%c %c\n", s[2], *(s+2));

  // read beyond str end; DON'T DO THIS
  //s1[4]==*(s1+4)
  //s1==&s1[0]
  //&s1[4]==&(*(s1+4))
  printf("%x %p %p\n", s1[4], s1, &s1[4]);

  // write beyond str end; DON'T DO THIS
  s1[4] = 'D';
  
  return 0;
}
```

out
```text
$ str
s 123 s1 123
1 1
3 3
0 0x0000000000003FA8 0x0000000000003FAC
```

```code
addr        val
0x3FA8      '1'   s1[0]
0x3FA9      '2'   s1[1]
0x3FAA      '3'   s1[2]
0x3FAB      '\0'  s1[3]
0x3FAC      '0'   s1[4] ← overflow
```