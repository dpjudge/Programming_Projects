/* Turing Machine Simulation
See Manual.txt for Description
See  Notes.txt for ... Notes.
*/

#include "DPJ.h"
#include "TM.h"

void main( int argc, char *argv[] )
{
// ***********************************************************************************************
// Define Problem elements and initialise with default values.
// ***********************************************************************************************
  int  Infinite               = INFINITE;    // Define and initialise Infinity
  int  Head;                                 // Define Tape Head position variable
  int  Start                  = STARTPROBLEM;// Define and initialise Start Tape position of Problem Data
  char   Problem_Data[]       = PROBLEMDATA; // Define and initialise Problem Data
  char  *Problem_Data_ptr     = Problem_Data;
  char **Problem_Data_ptr_ptr = &Problem_Data_ptr;
  int  Rules[][3]             = {RULES};

// ***********************************************************************************************
// There is either 1 arguement or 0 arguements.
// The only allowed arguement is a file defining a whole problem or adapting the default solution.
// ***********************************************************************************************

  if ( argc == 1 ) Error( WARNING, "No Problem file suggested : ",     // No Problem file!
                          NOARGS, "Continueing with default Problem" );// Complain and continue.
  else {
    if ( argc > 2 ) Error( WARNING, "Only 1 arguement expected : ",    // More than 1 arg?
                           EXCESSARG,                                  // accept first
                           "First arguement assumed to be Problem file" ); // ignore the rest.
// ***********************************************************************************************
// Test for non-existence or unreadable Problem file.
// If found, complain and continue with default.
// ***********************************************************************************************
    if ( access(argv[1], F_OK ) ) {      // access returns 0 (FALSE) on success??
      char Prefix[500];                  // vaguely valid reasons, but ... still bizarre!
      strcpy(Prefix,"Cannot find " ); strcat( strcat( Prefix, argv[1] ), " : " );
      Error( WARNING, Prefix, NOFILE, "Continueing with default Problem" );
    }  
    else if ( access(argv[1], R_OK ) ) { // access returns 0 (FALSE) on success??
      char Prefix[500];                  // vaguely valid reasons, but ... still bizarre!
      strcpy(Prefix,"Cannot read " ); strcat( strcat( Prefix, argv[1] ), " : " );
      Error( WARNING, Prefix, NOREAD, "Continueing with default Problem" );
    }
// ***********************************************************************************************
// If good Program file, read it and overwrite default settings as required.
// ***********************************************************************************************
    else {
      int  **Rules_ptr        = (int  **)&Rules[0][0];
      Read_Problem_File(argv[1], &Infinite, Problem_Data_ptr_ptr, Rules_ptr);
    }

  }

// ***********************************************************************************************
// Prepare Problem elements and Infinite Tape.
// ***********************************************************************************************

  char Tape[Infinite];                             // Create Infinite tape
  for ( Head = 0; Head < Infinite; Head++ ) Tape[Head] = EMPTY;
                                                   // Wipe infinite tape

  int  End           = strlen(Problem_Data_ptr) + Start - 1;
                           // Define and initialise End Tape position of Problem Data
  for ( Head = Start; Head < End; Head++ ) Tape[Head] = Problem_Data_ptr[Head - Start];
                           // Write Problem Data to Tape

  Head               = Start;

  char *Alphabet     = ALPHABET;

  int  Current_State = START;

// ***********************************************************************************************
// Run the Turing Machine on the defined problem.
// ***********************************************************************************************

  do {
    char *Current_Char_Address = strchr(Alphabet, Tape[Head]);
    int  Current_Char_Index    = (int)(Current_Char_Address - Alphabet);
    int  Rules_Row             = (Current_State * 3) + Current_Char_Index;

    fwrite(&Tape[490], 1, 80, stdout); printf("\n");
    for (int i = 0; i < Head - 490; i++ ) printf(" ");
    printf( "^\n" );

    Current_Char_Index     = Rules[Rules_Row][1];
    if (Current_Char_Index != SKIP) Tape[Head] = Alphabet[Current_Char_Index];

    Head = Head + Rules[Rules_Row][0];

    Current_State = Rules[Rules_Row][2];

  } while ( Current_State > ERROR );

  fwrite(&Tape[490], 1, 80, stdout); printf("\n");
  for (int i = 0; i < Head - 490; i++ ) printf(" ");
  printf( "^\n DONE\n" );

}

