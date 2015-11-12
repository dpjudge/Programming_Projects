#include <stdio.h>

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

/* Defines for this program */

#define MAXLINE 100
/* maximum input line size including any terminating '/n'
   used to specify string array, allows room for terminating '/0' as indexing
   commences at 0 */
#define  TABSIZE 8
#define  DOT  '.' /* for testing as visible BLANKS */
#define  DASH '-' /* for testing as visible TABS */

int  Getline(char line[], int maxline);

/* getline is now a standard part of stdio.h?
   http://man7.org/linux/man-pages/man3/getline.3.html
   which does not surprise me, vaguely remember using it.
   must be included after version 2 of K&R, which is surprising/interesting. */

/* read line replace spaces with TABS with spaces */

int  detabline(char line[], int linelength);
int  entabline(char line[], int linelength);
int   foldline(char line[], int linelength);

main()
{
  int len;            /* current line lengths */
  char line[MAXLINE]; /* current input line   */

  while ((len = entabline(line, MAXLINE)) > 0)
    printf("entabbed line is %d long:\n%s\n", len, line);

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

int entabline(char s[], int lim)
{
  int c;
  int charpos      = 0, printpos      = 0;
  int charincount  = 0, charoutcount  = 0;
  int tabincount   = 0, taboutcount   = 0;
  int blankincount = 0, blankoutcount = 0;

  do {

    int blanksout = 0, tabsout = 0;                  /* Set up counts of spaces and tabs to be output. */

    if ((c=getchar()) != EOF) {                /* get a new character. If it is not EOF, */
      charincount++;        /* count it as a character*/
      switch (c) {
        case BLANK : blankincount++; break; /* If appropriate, count it as a space */
        case TAB   : tabincount++;   break; /* If appropriate, count it as a tab */
      }
    }
    else break;

    if (charpos < lim) {                              /* Only if line not full,                         */

      int nexttab = TABSIZE - (printpos % TABSIZE);   /* calculate distance to next tabstop,            */

      switch (c) {

        case BLANK :                                  /* Whitespace? Not including EOL.                 */
        case TAB   :

          if (c == BLANK) {                           /* If first whitespace is a space,                */

            if (nexttab == 1) {                       /* If up to tabstop with just one space,          */

              if (charpos < lim) {                    /* Given there is still room,                     */
                s[charpos++] = BLANK;                 /* use the space in preference to a tab,          */
                blankoutcount++; charoutcount++;      /* count it,                                      */
                printpos++;
                nexttab = TABSIZE;                    /* set distance to tabstop to maximum,            */
                blanksout = 0;                        /* Reset blanks to print to zero.                 */
              }
            }
            else {
              nexttab--;
              blanksout++;                            /* Count it for future output.                    */

            }                                   
          }
          else {                                     /* If first whitespace is a tab,                  */
            if (charpos < lim) {                     /* Given there is still room,                     */
              s[charpos++] = TAB;                    /* use the tab in preference to any spaces        */
              taboutcount++; charoutcount++;         /* (should be none), count it,                    */
              blanksout = 0;                         /* throw away all initial spaces                  */
              printpos += nexttab;
              nexttab = TABSIZE;                     /* set distance to tabstop to maximum.            */
            }
          }

          while (((c=getchar()) == BLANK) ||
                              (c == TAB)) {          /* Keep reading until a non tab/space detected.   */
            charincount++;                           /* Count them all.                                */
            if (c == BLANK) {                        /* If a space,                                    */
              blankincount++;                        /* count it,                                      */
              if (nexttab == 0) {                    /* adjust distance to next tabstop.               */
                nexttab = TABSIZE;                   /* If tabstop reached, distance to next is maximum*/
                blanksout =0; tabsout++;             /* & trailing blanks can be replaced by a tab.    */
              }
              else {
                nexttab--; blanksout++;
              }
            }
            else {                                   /* If a tab,                                      */
              tabsout++;   tabincount++;             /* count it,                                      */
              nexttab = TABSIZE;                     /* adjust distance to next tabstop,               */
              blanksout = 0;                         /* Zero count of trailing spaces to be printed.   */
            }
          }    

          while (tabsout--   > 0) { if (charpos < lim) s[charpos++] = TAB;
                                            printpos += TABSIZE;
                                            taboutcount++;   charoutcount++; }
          while (blanksout-- > 0) { if (charpos < lim) s[charpos++] = BLANK;
                                            printpos++;
                                            blankoutcount++; charoutcount++; }
          if (c == EOF) break; else charincount++;

          /* Drop through to default to deal with extra side effect character which cannot be a space/tab/EOF */

        default:
          s[charpos++] = c; printpos++; charoutcount++;

      }

    }


  } while ((c != EOL) && (c != EOF));

  s[MIN(lim,charpos)]= '\0';

if (DEBUG) printf("\nTotal number of characters input:   %d\n"
                         "Total number of characters accepted %d\n"
                         "Number of tabs   accepted:          %d\n"
                         "Number of spaces accepted:          %d\n"
                         "Number of tabs   printed:           %d\n"
                         "Number of spaces printed:           %d\n"
                         "Printed length of line:             %d\n\n",
      charincount, charpos, tabincount, blankincount, taboutcount, blankoutcount, printpos);

  return MIN(lim,charpos);

}
