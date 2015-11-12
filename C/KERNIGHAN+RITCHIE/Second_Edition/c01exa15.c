#include <stdio.h>

#define MAXLINE 1000   /* maximum input line size    */

int max = 0;           /* maximum length seen so far */
char line[MAXLINE];    /* current input line         */
char longest[MAXLINE]; /* longest line saved here    */

int  Getline(void);
void copy(void);

/* print longest input line; specialized version */

main ()
{
  int len;
  extern int max;
  extern char longest[];

  while ((len = Getline()) > 0)
    if (len > max) {
      max = len;
      copy( );
    }

  if (max > 0) /* there was a line */
    printf("%s", longest);

  return 0;
}

/* Getline: specialized version */

int Getline(void)
{
  int c, i;
  extern char line[];

  for (i = 0; (i < MAXLINE-1)  
           && ((c = getchar()) != EOF)
           && (c != '\n'); ++i) line[i] = c;

  if (c == '\n') {
    line[i] = c;
    ++i;
  }

  line [i] = '\0';

  return i;

}

/* copy: specialized version */

void copy(void)
{
  int i = 0;
  extern char line[], longest[];

  while ((longest [i] = line[i]) != '\0') i++;

}
