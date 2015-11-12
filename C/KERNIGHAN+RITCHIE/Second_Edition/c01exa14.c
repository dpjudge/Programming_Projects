#include <stdio.h>

#define MAXLINE 1000

/* maximum input line size */

int  Getline(char line[], int maxline);

/* getline is now a standard part of stdio.h?
   http://man7.org/linux/man-pages/man3/getline.3.html
   which does not surprise me, vaguely remember using it.
   must be included after version 2 of K&R, which is surpring/interesting. */

void copyline(char to[], char from[]);

/* print longest input line */

main()
{
  int len;               /* current line length        */
  int max = 0;           /* maximum length seen so far */
  char line[MAXLINE];    /* current input line         */
  char longest[MAXLINE]; /* longest line saved here    */

  while ((len = Getline(line, MAXLINE)) > 0)
    if (len > max) {
      max = len;
      copyline(longest, line);
    }

  if (max> 0)  /* there was a line */ printf("\n\nThe line : %swas the longest.\n\n", longest);

  return 0;
}

/* getline: read a line into s, return length */

int Getline(char s[], int lim)
{
  int c, i;

  for (i = 0; (i < lim-1) && ((c=getchar()) != EOF) && (c != '\n'); ++i)
    s[i] = c;

  if (c == '\n') s[i++] = c;

  s[i]= '\0';

  return i;

}

/* copy: copy 'from' into 'to'; assume to is big enough */

void copyline(char to[], char from[])
{
  int i = 0;

  while ((to[i] = from[i]) != '\0') ++i;

}
