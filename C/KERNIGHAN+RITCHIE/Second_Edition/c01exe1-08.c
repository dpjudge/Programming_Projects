#include <stdio.h>

/* count lines and things in input */
/* Particularly blanks, tabs, and newline */
/* Presumably a blank is a space? */

#define BLANK ' '
#define EOL   '\n'
#define TAB   '\t'

main ()
{
  int c, nc = 0, nl = 0, nt = 0, nb = 0;

  while ((c = getchar()) != EOF) {
    nc++;
    if          (c == EOL  ) ++nl;
      else if   (c == BLANK) ++nb;
        else if (c == TAB  ) ++nt;

    printf("Character was: %c Numerically %d\n", c, c);
  }

  printf( "\n\nTotal number of characters: %d\n", nc);
  printf( "\n\nTotal number of lines:      %d\n", nl);
  printf( "\n\nTotal number of tabs:       %d\n", nt);
  printf( "\n\nTotal number of spaces:     %d\n", nb);

}
