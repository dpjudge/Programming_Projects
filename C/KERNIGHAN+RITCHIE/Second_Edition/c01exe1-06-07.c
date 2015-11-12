#include <stdio.h>

/* Find numerics value of (getchar() != EOF) */
/* Find numerics value of EOF and similar */

main( )
{
  int c, bool;

  while (bool=(getchar() != EOF)) {
    printf("getchar() != EOF is %d\n",bool);
    printf("When char is not EOF,\n");
  }
    printf("\n\ngetchar() != EOF is %d\n",bool);
    printf("When char is EOF,\n\n\n");
   
  while (bool=((c=getchar()) != EOF)) {
    putchar(c);
    printf("----c is %c %d -----\n",c,c);
    printf("----b is %d -----\n",bool);
  }

  printf("----EOF is %d b is %d -----\n",EOF,bool);
  printf("----newline is %d -----\n",'\n');
  printf("----tab is %d -----\n",'\t');

}
