#include <stdio.h>

/* count lines and things in input */

main ()
{
  int c, nc = 0, nl = 0;

  while ((c = getchar()) != EOF) {
    nc++; if (c == '\n' ) ++nl;
    printf("Character was: %c Numerically %d\n", c, c);
  }

  printf( "\n\nTotal number of characters: %d\n", nc);
  printf( "\n\nTotal number of lines:      %d\n", nl);

}
