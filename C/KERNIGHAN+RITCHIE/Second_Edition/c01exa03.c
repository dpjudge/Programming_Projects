#include <stdio.h>

#define LOWER 0   /* lower limit of temperature table */
#define UPPER 300 /* upper limit */
#define STEP 20   /* step size */

/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300 */

main ()
{
  float fahr, celsius;

  fahr = LOWER;
  while (fahr <= UPPER) {
    celsius = (5.0/9.0) * (fahr-32.0);
    printf("%3.0f\t%10.5f\n", fahr, celsius);
    fahr = fahr + STEP;
  }
}
