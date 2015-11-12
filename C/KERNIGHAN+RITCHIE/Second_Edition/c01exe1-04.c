#include <stdio.h>

#define LOWER -17   /* lower limit of temperature table */
#define UPPER 150 /* upper limit */
#define STEP 10   /* step size */

/* print Celsius-Fahrenheit table
   With a Heading

   for fahr = 0, 20, ..., 300 */

main ()
{
  float fahr, celsius;

  printf("%s","A table for changing temperstures from Stupid Celsius ones to Real farenheit.\n"
              "=============================================================================\n"
              "Celsius\t\tFarenheit\n"
              "---------\t-------\n");
  celsius = LOWER;
  while (celsius <= UPPER) {
    fahr = celsius * (9.0/5.0) + 32.0;
    printf("%3.0f\t\t%10.5f\n", celsius, fahr);
    celsius = celsius + STEP;
  }
}
