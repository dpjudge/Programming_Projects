/* Turing Machine Simulation

--------------------------------------------
2018.03.31:
===========
  Quite easy really ... not what I recall from 1978?
  Must look at that when it comes to the surface
  Mind you, this is all nonsense as one still does not
  understand fully Turing completeness etc.
  Bit like bwa implementation versus why it is important?
  Or ... explaining brown bear graphs without the reason for
  their existence wrt velvet and freinds (a lesser crime as
  this link is relatively transparent)
  What the hell ... filled the space where life should be
  for a happily papssed moment of ten
  Far to many moments actually!!! Should have been able to
  knock this one out much faster surely!? Not even very pretty code.

  Might tidy up sometime? Read problems from files? Data checking!!!
  Hmmm ... but why Dave?

  .... bad question! Never has an answer

  Do it in Python? Some things would be very neat I think?
  Is there not a dictionary, tuple, whatevr here and there?
  and that bit about finding a char positionin a string would
  be trivial!

  Pity PYTHON is only for boys and women :-)

  Not a good entrance to C++ methinks,but probably wrong here?
  Never get around to  C++ dear boy. Stay with the obtainable!

--------------------------------------------
  Basically:

     Setup up an example tape
       Define and Wipe
     Setup up an example set of Rules/States
       Define and initialise according to notes below

     Do it?

  Where "Do it" I have in my head and will allow to dribble onto the
  page in disorder.

  Also must think of the Problem. I start with Add one to a given number.
  This I bolt into the code in afashion that can be, optionally,
  overwrittn by other problems from files.

  So, specifically, the "Add One" Rules

  Problems, generally can be a series of rows of 3 integers representing
  DIRECTION (for Tape Head to move), NEXT_CHAR (to be written to current
  Tape Head position) and NEXT_STATE (to determine next actions).

  The Rows to be ordered by state and then by Current Tape Character (ranked by position in the allowed alphabet)
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "DPJ.h"
#include "TM.h"

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

