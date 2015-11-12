#include <stdio.h>

/* Defines I like */

#define TRUE  1
#define FALSE 0

#define BLANK ' '
#define TAB   '\t'
#define EOL   '\n'

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

/* Defines for this program */

#define MAXLINE 100

/* maximum input line size including any terminating '/n'
   used to specify string array, allows room for terminating '/0' as indexing
   commences at 0 */

#define MINPRINT 80 /* All lines longer than MINPRINT to be printed */

int  Getline(char line[], int maxline);

/* getline is now a standard part of stdio.h?
   http://man7.org/linux/man-pages/man3/getline.3.html
   which does not surprise me, vaguely remember using it.
   must be included after version 2 of K&R, which is surpring/interesting. */

void copyline(char to[], char from[]);

/* print all lines > 80 */

main()
{
  int len;                 /* current line length        */
  int max = 0;             /* maximum length seen so far */
  char line[MAXLINE];      /* current input line         */
  char longest[MAXLINE];   /* longest line saved here    */

  while ((len = Getline(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copyline(longest, line);
    }

    if (len >= MINPRINT) {
      printf("\n\nThe line : \n%s\nwas long enough to print (>= %d characters)\n"
             "specifically %d characters.\n\n", line, MINPRINT, len);
    if (len > MAXLINE) printf("Maximum line length exceeded (%d charaters), excess input lost.\n\n", MAXLINE);
    }
  }

  if (max > 0) {
    printf("\n\nThe line : \n%s\nwas the longest (%d characters).\n\n", longest, max);
    if (max > MAXLINE) printf("Maximum line length exceeded (%d charaters), excess input lost.\n\n", MAXLINE);
  }
  else printf("\n\nNo input????\n\n");

  return 0;
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

/* copy: copy 'from' into 'to'; assume to is big enough */

void copyline(char to[], char from[])
{
  int i = 0;

  while ((to[i] = from[i]) != '\0') ++i;

}
