/* Basic includes  */

#include <stdio.h>
#include <stdlib.h>

/* Defines I like */

#define TRUE     1
#define FALSE    0

#define STRMATCH 0     // str(n)cmp(a,b) returns -x, 0, +x for a>b, a=b, a<b. Novel, but ...

#define DEBUG    TRUE

#define BLANK    ' '
#define SPACE    BLANK
#define TAB      '\t'
#define EOL      '\n'
#define nul      '\0'

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// ***********************************************************************************************
// Dealing with ERROR/WARNING messages.
// Probably should go to stderr?
// ***********************************************************************************************

#define MAXLENERROR 256

#define NOARGS        0
#define EXCESSARG     1
#define NOFILE        2
#define NOREAD        3
#define BADARG        4
#define UNKARG        5

char Error_prefix[MAXLENERROR];
char *ERROR_MESSAGES[] = {
       "Arguements Expected",
       "Too many arguments",
       "File does not exist",
       "No read access to file",
       "Illegal arguement prefix",
       "Unknown arguement",
       "5555555555" };
char Error_suffix[MAXLENERROR];

#define WARNING 0
#define ERROR   1
char *Severity[] = { "Warning: ", "Error  : " };

void Error( int Gravity, char *Prefix, int Index, char *Suffix ) {
  printf("%s%s%s - %s\n", Severity[Gravity], Prefix, ERROR_MESSAGES[Index], Suffix );
  return;
}
