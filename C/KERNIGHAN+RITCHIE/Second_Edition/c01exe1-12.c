#include <stdio.h>

/* print each word on separate line */


#define TRUE  1
#define FALSE 0

#define BLANK ' '
#define TAB   '\t'
#define EOL   '\n'

main ()
{
  int c, state = FALSE;

  while ((c = getchar()) != EOF) {

    if (c == EOL || c == BLANK || c == TAB) {
      if (state) { putchar(EOL); state = FALSE; };
    }
    else         { putchar(c); state = TRUE;   };

  }

  putchar(EOL);

}
