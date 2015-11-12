#include <stdio.h>
#include <stdlib.h>
#include "include/local.h"

/* Constant Declarations */

#define LOWER -17 /* lower limit of temperature table */
#define UPPER 150 /* upper limit */
#define STEP 10   /* step size */
#define CFRATIO (9.0/5.0) /* Celsius to Fahrenheit ratio */
#define FCRATIO (5.0/9.0) /* Fahrenheit to Celsius ratio */

/* Function Declarations */

float fahrenheit(float celsius);

main ()
{
  float celsius = LOWER;

  printf("%s","A table for changing temperstures from Stupid Celsius ones to Real farenheit.\n"
              "=============================================================================\n"
              "Celsius\t\tFarenheit\n"
              "---------\t-------\n");

  while (celsius <= UPPER) {
    printf("%3.0f\t\t%10.5f\n", celsius,fahrenheit(celsius));
    celsius = celsius + STEP;
  }

  return SUCCESS;
}

/* Function Definitions */

/* fahrenheit: Convert Celsius to Fahrenheit */

float fahrenheit(float celsius) { return (celsius * CFRATIO + 32.0); }

