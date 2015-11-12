#include <stdio.h>

/* count characters in input; 2nd version */

main( )
{
  double nc;

  for (nc=0; getchar()!=EOF; ++nc);
/* Horrible! Its a while? */

  printf("\n\n%.0f\n\n", nc);
  printf("%.0f\n", nc);

}
