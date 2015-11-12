#include <stdio.h>

#define LOWER 0   /* lower limit of temperature table */
#define UPPER 300 /* upper limit */
#define STEP 20   /* step size */

/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300 */

main ()
{
  int fahr, celsius;

  fahr = LOWER;
  while (fahr <= UPPER) {
    celsius = 5 * (fahr-32) / 9;
    printf("%d\t%d\n", fahr, celsius);
    fahr = fahr + STEP;
  }
}
