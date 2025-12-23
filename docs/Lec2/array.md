```c
#include "kernel/types.h"
#include "user/user.h"

int a[3] = {1, 2, 3};        // an array of 3 int's
char b[3] = {'a', 'b', 'c'}; // an array of 3 char's

int
main(int ac, char **av)
{
  // first element is at index 0
  printf("%d\n", a[0]);

  a[1] += 1;    // use index access
  *(a + 2) = 5; // pointer access

  printf("%d %d\n", a[1], a[2]);

  // pointers to array elements
  //         &*p == p
  //&a[2] == &(*(a+2)) == a+2
  printf("a %p a1 %p a2 %p a2 %p\n", a, a + 1, a + 2, &a[2]);

  // pointer arithmetic uses type
  printf("%p %p\n", b, b + 1);

  return 0;
}
```

out
```text
$ array
1
3 5
a 0x0000000000001010 a1 0x0000000000001014 a2 0x0000000000001018 a2 0x0000000000001018
0x0000000000001000 0x0000000000001001
```