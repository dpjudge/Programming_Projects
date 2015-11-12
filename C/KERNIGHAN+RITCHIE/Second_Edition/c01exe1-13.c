#include <stdio.h>
#include <stdlib.h>

/* print word size histogram */


#define TRUE  1
#define FALSE 0

#define BLANK ' '
#define TAB   '\t'
#define EOL   '\n'

#define MAX_WS 20
#define DIG_WS "%2d "
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

main ()
{
  int c, i, wl = 0, state = FALSE;
  int hist[MAX_WS];

  for (i = 0; i <= MAX_WS; i++) hist[i] =0;

  while ((c = getchar()) != EOF) {

    if (c == EOL || c == BLANK || c == TAB) {
      if (state) { hist[MIN(MAX_WS,wl)]++; state = FALSE; wl = 0; };
    }
    else         { wl++; state = TRUE;   };

  }

  putchar(EOL);
  for (wl = 0; wl <= MAX_WS; wl++) {
    printf(DIG_WS, wl);
    for (i = 1; i <= hist[wl]; i++) putchar('=');
    putchar(EOL);
  };

  putchar(EOL);

}

