#include <stdio.h>
#include <stdlib.h>

/* print char frequency histogram */


#define TRUE  1
#define FALSE 0

#define BLANK ' '
#define TAB   '\t'
#define EOL   '\n'

#define MAX_CS 255
#define DIG_CS "%3d "
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

main ()
{
  int c, i, j, hist[MAX_CS];

  for (i = 0; i <= MAX_CS; i++) hist[i] =0;

  while ((c = getchar()) != EOF) hist[MIN(MAX_CS,c)]++;

  putchar(EOL);
  for (i = 0; i <= MAX_CS; i++) {
    if (hist[i] != 0) {
      printf(DIG_CS, i);
      for (j = 1; j <= hist[i]; j++) putchar('=');
      putchar(EOL);
    };
  };

  putchar(EOL);

}

