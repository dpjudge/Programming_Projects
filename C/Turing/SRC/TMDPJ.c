/* Turing Machine Simulation

See Manual.txt for Description
See  Notes.txt for ... Notes.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>    // Not needed currently, but maybe if I try strcspn
                       // to find chars in Alphabet (see Notes.txt).
#include <string.h>
#include "DPJ.h"
#include "TM.h"

void main( int argc, char *argv[] )
{
switch ( argc ) {
  case 1 :
    printf("No Problem file - Continueing with default Problem");
    break; 
  case 2 :
    if ( access(argv[1], F_OK ) ) {         // access returns 0 (FALSE) on success??
                                            // vaguely valid reasons, but ... still bizarre!
      char Prefix[500];
      strcpy(Prefix,"Cannot find " );
      strcat( strcat( Prefix, argv[1] ), " : " );
      Error( WARNING, Prefix, NOFILE, "Continueing with default Problem" );
      break;
    }  
    if ( access(argv[1], R_OK ) ) {         // access returns 0 (FALSE) on success??
                                            // vaguely valid reasons, but ... still bizarre!
      char Prefix[500];
      strcpy(Prefix,"Cannot read " );
      strcat( strcat( Prefix, argv[1] ), " : " );
      Error( WARNING, Prefix, NOREAD, "Continueing with default Problem" );
      break;
    }
    int c;
    FILE *file;
    file = fopen(argv[1], "r");
    if (file) {
      while ((c = getc(file)) != EOF) putchar(c);
    fclose(file);
    }
    break;
  default :
         printf("Invalid grade\n" );
  }

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
for ( Head = Start; Head < End; Head++ ) { Tape[Head] = Problem[Head - Start]; };
                         // Write Problem Data to Tape

int Rules[][3]={RULES};

int State = 1;
Head = Start;

char *Alphabet     = ALPHABET;

Head               = Start;
int  Current_State = 2;

// If it exists, read problem from file



// If it exists, read problem from file

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

