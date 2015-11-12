#include <stdio.h>

#define LOWER 0   /* lower limit of temperature table */
#define UPPER 300 /* upper limit */
#define STEP 20   /* step size */

/* print Fahrenheit-Celsius table
   With a Heading

   for fahr = 0, 20, ..., 300 */

main ()
{
  float fahr, celsius;

  printf("%s","A table for changing temperstures from real farenheit ones to Stupid Celsius.\n"
              "=============================================================================\n"
              "Farenheit\tCelsius\n"
              "---------\t-------\n");
  fahr = LOWER;
  while (fahr <= UPPER) {
    celsius = (5.0/9.0) * (fahr-32.0);
    printf("%3.0f\t\t%10.5f\n", fahr, celsius);
    fahr = fahr + STEP;
  }
}
