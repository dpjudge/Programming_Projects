#include <stdio.h>

/* tab to \t and \ to \\ */

#define BLANK ' '
#define TAB   '\t'
#define BS    '\\'

main ()
{
  int c;

  while ((c = getchar()) != EOF) {
    if   (c == TAB) { putchar(BS); c='t'; }
      if (c == BS)  { putchar(BS); c=BS;  };
    putchar(c);
  }

}
