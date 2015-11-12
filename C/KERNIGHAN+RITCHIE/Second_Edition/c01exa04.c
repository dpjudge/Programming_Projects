#include <stdio.h>

/* print Fahrenheit-Celsius table = alternative */

main( )
  {
    int fahr;
    float ratio = 5.0/9.0;

    for (fahr = 0; fahr <= 300; fahr += 20)
      printf("%3d %6.1f\n", fahr, ratio*(fahr-32));

  }
