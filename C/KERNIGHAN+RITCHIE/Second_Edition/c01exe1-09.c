#include <stdio.h>

/* Remove multiple spaces */

#define BLANK ' '

main ()
{
  int c, nb = 0, lostb =0;

  while ((c = getchar()) != EOF)
    if (c == BLANK)
      if (nb++ != 0) { lostb++; printf("nb is:%d\n",nb); }
      else putchar(c);
    else { nb = 0; putchar(c); };

  printf("\n\nTotal number of spaces delated was: %d\n", lostb);

}
