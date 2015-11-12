#include <stdio.h>

#define LOWER   0   /* lower limit of temperature table */
#define UPPER 300   /* upper limit */
#define STEP   20   /* step size */

/* Print Fahrenheit to Celsius table */

main ()
{
  int   fahr;
  float ratio = 5.0/9.0;

  for (fahr = LOWER; fahr <= UPPER; fahr += STEP)
    printf("%3d %6.1f\n", fahr, ratio * (fahr - 32));
}
