#include <stdio.h>

/* Defines I like */

#define TRUE  1
#define FALSE 0

#define BLANK ' '
#define SPACE BLANK
#define TAB   '\t'
#define EOL   '\n'
#define nul   '\0'

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

/* Defines for this program */

#define MAXLINE 100
/* maximum input line size including any terminating '/n'
   used to specify string array, allows room for terminating '/0' as indexing
   commences at 0 */
#define  TABSIZE 8
#define DOT '.' /* for testing as visible BLANKS */

int  Getline(char line[], int maxline);

/* getline is now a standard part of stdio.h?
   http://man7.org/linux/man-pages/man3/getline.3.html
   which does not surprise me, vaguely remember using it.
   must be included after version 2 of K&R, which is surpring/interesting. */

/* read line replace tabs with spaces */

int  detabline(char line[], int linelength);
int  entabline(char line[], int linelength);
int  foldline(char line[], int linelength);

main()
{
  int len;            /* current line lengths */
  char line[MAXLINE]; /* current input line   */

  while ((len = detabline(line, MAXLINE)) > 0)
    printf("Detabbed line is:\n%s\n", line);

}

/* getline: read a line into s, return length */

int Getline(char s[], int lim)
{
  int c, i = 0;

  while ((c=getchar()) != EOF) {
    if (i < lim) s[i] = c;
    i++;
    if (c == EOL) break;
  }

  s[MIN(lim,i)]= '\0';

  return MIN(lim,i);

}

/* detab: read a line into s, detab, return length */

int detabline(char s[], int lim)
{
  int c, i = 0;

  while ((c=getchar()) != EOF) {
    if (i < lim) {
      if (c == TAB) {
        int blankcount, tabsize = TABSIZE - (i % TABSIZE);

        for (blankcount = 0; (blankcount < tabsize)
                          && (i < lim); blankcount++) s[i++] = DOT;
        printf("\nTab replaced by %d spaces at position %d\n",
                                        blankcount, (i-- - blankcount + 1));
                  /* Feels bad to rely on print statement to set i correctly?
                     But .... what the hell, my world that says hello to no one :-) */
      }
      else s[i] = c;
    }
    i++;
    if (c == EOL) break;
  }

  s[MIN(lim,i)]= '\0';

  return MIN(lim,i);

}
