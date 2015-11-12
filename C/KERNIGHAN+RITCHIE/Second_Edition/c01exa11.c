#include <stdio.h>

/* count lines, words, and characters in input */


#define TRUE  1
#define FALSE 0

#define BLANK ' '
#define TAB   '\t'
#define EOL   '\n'

main ()
{
  int c, nl = 0, nw = 0, nc = 0, state = FALSE;

  while ((c = getchar()) != EOF) {

    ++nc;

    if (c == EOL) {
      ++nl; state = FALSE;
      }

    else if (c == BLANK || c == TAB) state = FALSE;

    else if  ((c != EOL) && !state) { state = TRUE; ++nw; };

    putchar(c);
  }

  printf ("\n\nLines:%d\nWords: %d\nChars: %d\n", nl, nw, nc);

}
