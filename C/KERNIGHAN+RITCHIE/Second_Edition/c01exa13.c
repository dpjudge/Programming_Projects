#include <stdio.h>
#include <stdlib.h>
#include "include/local.h"

/* Looking at simple functions */

/* Function Declarations */

int power(int base, int exponent);

/* test power function */

main ()
  {
    int i;
    for (i = 0; i < 10; ++i)
      printf("i = %d 2^i = %d -3^i -= %d\n", i, power(2,i), power(-3,i));

    return 0;
  }

/* Function Definitions */

/* power: raise base to n-th power; n >= 0 */
int power(int base, int exponent)
  {
    int i, power = 1;

    for (i = 1; i <= exponent; ++i) power = power * base;

    return power;
  }
