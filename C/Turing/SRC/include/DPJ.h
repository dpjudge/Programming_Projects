// ===============================================================================================
// Basic includes
// ===============================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ===============================================================================================
// Defines I like
// ===============================================================================================

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

// ===============================================================================================
// Functions I like
// ===============================================================================================

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

// ***********************************************************************************************
// Remove whitespace from both ends of a string, returning the trimmed substring
// Shamelessly copied from:
// https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
// ***********************************************************************************************

// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

// ***********************************************************************************************
// Remove whitespace from both ends of a string, returning the size of the trimmed substring, which
// is copied to an output buffer of sufficient size.
// Again, shamelessly copied from:
// https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
// ***********************************************************************************************

// Stores the trimmed input string into the given output buffer, which must be
// large enough to store the result.  If it is too small, the output is
// truncated.

size_t trimcpywhitespace(char *out, size_t len, const char *str)
{
  if(len == 0) return 0;

  const char *end;
  size_t out_size;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0) { *out = 0; return 1; } // All spaces?

  // Trim trailing space
  end = str + strlen(str) - 1; while(end > str && isspace((unsigned char)*end)) end--; end++;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  out_size = (end - str) < len-1 ? (end - str) : len-1;

  // Copy trimmed string and add null terminator
  memcpy(out, str, out_size); out[out_size] = 0;

  return out_size;
}
