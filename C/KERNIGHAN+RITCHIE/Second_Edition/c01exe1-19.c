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

#define MAXLINE 50

/* maximum input line size including any terminating '/n'
   used to specify string array, allows room for terminating '/0' as indexing
   commences at 0 */

#define MINPRINT 10 /* All lines longer than MINPRINT to be printed */

int  Getline(char line[], int maxline);

/* getline is now a standard part of stdio.h?
   http://man7.org/linux/man-pages/man3/getline.3.html
   which does not surprise me, vaguely remember using it.
   must be included after version 2 of K&R, which is surpring/interesting. */

int  trimline(char line[], int linelength);

void copyline(char to[], char from[]);
void reverseline(char forward[], char reverse[], int linelen);

/* print all trimmed lines > 80                     */
/* remove all trimmed lines that are all whitespace */
/* print longest trimmed line                       */

main()
{
  int initlen,trimlen;     /* current line lengths        */
  int max = 0;             /* maximum length seen so far  */
  char initline[MAXLINE];  /* current input line as typed */
  char revline[MAXLINE];   /* current input line reversed */
  char longline[MAXLINE];  /* longest line saved here     */

  while ((trimlen = initlen = Getline(initline, MAXLINE)) > 0) {
    trimlen = trimline(initline, initlen);
    reverseline(initline, revline, trimlen);
    if (trimlen > max) {
      max = trimlen;
      copyline(longline, revline);
    }

    if (trimlen >= MINPRINT) {
      printf("\n\nThe trimmed & reversed line : \n%s\nwas long enough to print (>= %d characters)\n"
             "specifically %d characters.\n\n", revline, MINPRINT, trimlen);
      if (initlen > MAXLINE)
        printf("Maximum untrimmed line length exceeded (%d charaters), excess "
               "input lost.\n\n", MAXLINE);
    }

    if (trimlen < initlen)
      printf("Initial line trimmed & reversed from %d to %d characters by removal of trailing white space\n\n",initlen,trimlen);

    if (trimlen == 0)
      printf("Line rejected. Nothing other than whitespace characters\n\n");
  }

  if (max > 0) {
    printf("\n\nThe line : \n%s\nwas the longest (%d characters).\n\n", longline, max);
    if (max > MAXLINE) printf("Maximum line length exceeded (%d charaters), excess input lost.\n\n", MAXLINE);
  }
  else printf("\n\nNo input???? So no maxline to print.\n\n");

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

/* trimline: remove white space from the end of s */
/* retain '\n' termination if present             */

int trimline(char s[], int len)
{
  int c, i = len - 1;

  if (s[i] == EOL) i--; 

  while (i >= 0) {
    if ((s[i] == BLANK) || (s[i] == TAB) || (s[i] == EOL)) { s[i--] = nul; len--; }
    else break;
  }

  if ((len == 1) && (s[0] == EOL)) s[--len] = nul; /* Disallow a line that is just an EOL */

  return len;

} 


/* copy: copy 'from' into 'to'; assume to is big enough */

void copyline(char to[], char from[])
{
  int i = 0, j ;

  while ((to[i] = from[i]) != '\0') ++i;

}


/* reverse_string: copy in reverse order 'from' into 'to'; assume to is big enough */

void reverseline(char forward[], char reverse[], int linelen)
{
  int i = 0, j = linelen;

  reverse[linelen] = forward[j--];

  while (j >= 0) reverse[i++] = forward[j--];

}
