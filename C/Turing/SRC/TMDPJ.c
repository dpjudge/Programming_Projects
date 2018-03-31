/* Turing Machine Simulation

--------------------------------------------
2018.03.31:
===========
  Quite easy really ... not what I recall from 1978? Must look at that when it comes to the surface
  Mind you, this is all nonsense as one still does not understand fully Turing completeness etc.
  Bit like bwa and why it is important
  What the hell ... filled the space where life should be for a while

  Might tidy up sometime? Read problems from files? Data checking!!!
  Hmmm ... but why Dave?
  .... bad question! Never has an answer

  Do it in Python?
  Not a good entrance to C++ methinks

--------------------------------------------

  Setup up an example tape
  Setup up an example set of Rules/States

  Do it?

*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

#define INFINITE   1000
#define STARTHEAD  INFINITE/2
#define EMPTY      '~'

#define MAXSTATES  50

#define ALPHABET   "01~"
#define SKIP       -1
#define PROBLEM    "111111111110111111111111111111111111"

#define LEFT       -1
#define HOLD       0
#define RIGHT      1

#define HALT       0   // Define mandatory HALT  State as first  State
#define ERROR      1   // Define mandatory ERROR State as second State
#define START      2   // Define mandatory START State as third State
#define RULES      {HALT,HALT,HALT},{HALT,HALT,HALT},{HALT,HALT,HALT},\
                   {ERROR,ERROR,ERROR},{ERROR,ERROR,ERROR},{ERROR,ERROR,ERROR},\
                   {RIGHT,SKIP,3},{RIGHT,SKIP,3},{HOLD,SKIP,ERROR},\
                   {RIGHT,SKIP,3},{RIGHT,SKIP,3},{LEFT,SKIP,4},\
                   {HOLD,1,5},{LEFT,0,4},{HOLD,1,HALT},\
                   {LEFT,SKIP,5},{LEFT,SKIP,5},{RIGHT,SKIP,HALT}

void main()
{

int Head;                // Define Tape Head position variable

int Infinite = INFINITE; // Define and initialise Infinity
char Tape[INFINITE];     // Create Infinite tape
for ( Head = 0; Head < INFINITE; Head++ ) { Tape[Head] = EMPTY; };
                         // Wipe infinite tape

char Problem[] = PROBLEM;// Define and initialise Problem Data
int  Start     = STARTHEAD;
                         // Define and initialise Start Tape position of Problem Data
int  End       = sizeof(Problem) + Start - 1;
                         // Define and initialise End   Tape position of Problem Data
for ( Head = Start; Head < End; Head++ ) { Tape[Head] = Problem[Head - Start]; 

};
                         // Write Problem Data to Tape

int Rules[][3]={RULES};

int State = 1;
Head = Start;

/*
Find the position in the alphabet of the current Tape character
Dead easy in Python! But we are men! ... sometimes ...

These solutions at:
https://stackoverflow.com/questions/3217629/how-do-i-find-the-index-of-a-character-within-a-string-in-c

Most opine this as the best solution:

""""""""""""""""""""""""""""""""""
char *string = "qwerty";
char *e;
int index;

e = strchr(string, 'e');
index = (int)(e - string);
""""""""""""""""""""""""""""""""""
I wonder, if it was a very long string, could one assume it was in contiguous memory? Probably not? Maybe the compiler would fix such an issue? Must surely?

Also says:
"You can also use strcspn(string, "e") but this may be much slower since it's able to handle searching for multiple possible characters. Using strchr and subtracting the pointer is the best way."

Maybe I try strcspn sometime, but ... the pointers make me feel good :-)

*/

char *Alphabet     = ALPHABET;

Head               = Start;
int  Current_State = 2;

do {
    char *Current_Char_Address = strchr(Alphabet, Tape[Head]);
    int  Current_Char_Index    = (int)(Current_Char_Address - Alphabet);
    int Rules_Row              = (Current_State * 3) + Current_Char_Index;

fwrite(&Tape[490], 1, 80, stdout); printf("\n");
for (int i = 0; i < Head - 490; i++){printf(" ");}; printf("^\n");

    Current_Char_Index     = Rules[Rules_Row][1];
    if (Current_Char_Index != SKIP) { Tape[Head] = Alphabet[Current_Char_Index];};

    Head = Head + Rules[Rules_Row][0];

    Current_State = Rules[Rules_Row][2];

  } while (Current_State > ERROR);


fwrite(&Tape[490], 1, 80, stdout); printf("\n");
for (int i = 0; i < Head - 490; i++){printf(" ");}; printf("^\n DONE\n");

printf("\n\n\nxxx %s yyy\n", Tape);
}

