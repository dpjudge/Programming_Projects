#include <stdio.h>

/* count digits, white space, others */

#define TRUE  1
#define FALSE 0

#define BLANK ' '
#define TAB   '\t'
#define EOL   '\n'

main ()
{

  int c, i, nwhite = 0, nother = 0;
  int ndigit[10];

  for (i = 0; i < 10; ++i)
    ndigit[i] = 0;

  while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')                    ++ndigit[c-'0'];
    else if (c == EOL || c == BLANK || c == TAB) ++nwhite;
    else                                         ++nother;

  printf("digits =");
  for (i = 0; i < 10; ++i)
    printf(" %d", ndigit[i]);
  printf(", white space = %d, other = %d\n", nwhite, nother);

}
