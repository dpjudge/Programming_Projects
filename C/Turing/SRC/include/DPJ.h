#include <stdlib.h>

/* Defines I like */

#define TRUE  1
#define FALSE 0

#define DEBUG TRUE

#define BLANK ' '
#define SPACE BLANK
#define TAB   '\t'
#define EOL   '\n'
#define nul   '\0'

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define EXCESSARG 0
#define NOFILE    1
#define NOREAD    2

char *ERROR_MESSAGES[] = {
       "Too many arguments",
       "File does not exist",
       "No read access to file",
       "3333333333",
       "4444444444",
       "5555555555" };

#define WARNING 0
#define ERROR   1
char *Severity[] = { "Warning: ", "Error  : " };

void Error( int Gravity, char *Prefix, int Index, char *Suffix ) {
  printf("%s%s%s - %s\n", Severity[Gravity], Prefix, ERROR_MESSAGES[Index], Suffix );
  return;
}
