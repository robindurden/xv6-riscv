#include "kernel/types.h"
#include "user/user.h"

char *s = "123"; // readonly data
char *p = "123";
char a[3] = {'1', '2', '3'};
int
main(int ac, char **av)
{
  printf("%p\n", p);
  printf("%c\n", *p);
  printf("%p\n\n", &p);
  char s1[4] = {'1', '2', '3', '\0'}; // in stack

  // s and s1 are strings
  printf("s %s s1 %s\n", s, s1);

  // can use index or pointer access
  // s[0]==*(s+0)
  // *s==*(s+0)
  printf("%c %c\n", s[0], *s);
  printf("%c %c\n", s[2], *(s + 2));

  // read beyond str end; DON'T DO THIS
  // s1[4]==*(s1+4)
  //&s1[4]==&(*(s1+4))
  printf("%x %p %p\n", s1[4], s1, &s1[4]);

  // write beyond str end; DON'T DO THIS
  s1[4] = 'D';

  return 0;
}