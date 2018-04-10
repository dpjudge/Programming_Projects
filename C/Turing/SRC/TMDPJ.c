/* Turing Machine Simulation
See Manual.txt for Description
See  Notes.txt for ... Notes.
*/

#include "DPJ.h"
#include "TM.h"

int main( int argc, char *argv[] )
{

// ***********************************************************************************************
// Define Problem elements and initialise with default values.
// ***********************************************************************************************

  int  infinite               = INFINITE;          // Define and initialise Infinity
  int  head;                                       // Define Tape head position variable
  int  start_head             = STARTHEAD;


  char  Problem_Data[]        = PROBLEMDATA;       // Define and initialise Problem Data
  char *Problem_Data_ptr      = Problem_Data;      //
  int  start_data             = STARTPROBLEM;      // Define and initialise Start Tape position of Problem Data
  int  free_Problem_Data      = FALSE;             //

  char  Alphabet[]            = ALPHABET;          //
  char *Alphabet_ptr          = Alphabet;          //
  int  alphabet_size          = strlen(Alphabet);  //
  int  free_alphabet          = FALSE;             //

  int  state_count            = STATECOUNT;        //
  int  rules_size             = alphabet_size      //
                                 * state_count * 3;//
  int   Rules[]               = {RULES};           //
  int  *Rules_ptr             = Rules;             //
  int  free_Rules             = FALSE;             //

// ***********************************************************************************************
// There is either 1 arguement or 0 arguements.
// The only allowed arguement is a file defining a whole problem or adapting the default solution.
// ***********************************************************************************************

  if ( argc == 1 ) Error( WARNING, "No Problem file suggested : ",        // No Problem file!
                          NOARGS,  "Continueing with default Problem" );  // Complain and continue.
  else {
    if ( argc > 2 ) Error( WARNING, "Only 1 arguement expected : ",       // More than 1 arg?
                           EXCESSARG,                                     // accept first
                           "First arguement assumed to be Problem file" );// ignore the rest.

// ***********************************************************************************************
// Test for non-existence or unreadable Problem file.
// If found, complain and continue with default.
// ***********************************************************************************************

    if ( access(argv[1], F_OK ) ) {      // access returns 0 (FALSE) on success??
      char Prefix[500];                       // vaguely valid reasons, but ... still bizarre!
      strcpy(Prefix,"Cannot find " ); strcat( strcat( Prefix, argv[1] ), " : " );
      Error( WARNING, Prefix, NOFILE, "Continueing with default Problem" );
    }

    else if ( access(argv[1], R_OK ) ) {      // access returns 0 (FALSE) on success??
      char Prefix[500];                       // vaguely valid reasons, but ... still bizarre!
      strcpy(Prefix,"Cannot read " ); strcat( strcat( Prefix, argv[1] ), " : " );
      Error( WARNING, Prefix, NOREAD, "Continueing with default Problem" );
    }

// ***********************************************************************************************
// If good Program file, read it and overwrite default settings as required.
// ***********************************************************************************************

    else {
      Read_Problem_File(argv[1], &infinite, &start_head,
                                 &Problem_Data_ptr, &start_data, &free_Problem_Data,
                                 &Alphabet_ptr, &alphabet_size, &free_alphabet,
                                 &state_count, &rules_size, &Rules_ptr, &free_Rules);

    }

  }

// ***********************************************************************************************
// Prepare Problem elements and Infinite Tape.
// ***********************************************************************************************

  char Tape[infinite];                             // Create Infinite tape
  for ( head = 0; head < infinite; head++ ) Tape[head] = EMPTY;
                                                   // Wipe infinite tape

  int  end_data      = strlen(Problem_Data_ptr) + start_data - 1;
                           // Define and initialise End Tape position of Problem Data
  for ( head = start_data; head < end_data; head++ ) Tape[head] = Problem_Data_ptr[head - start_data];
                           // Write Problem Data to Tape

  head               = start_head;

  int  Current_State = START;

// ***********************************************************************************************
// Run the Turing Machine on the defined problem.
// ***********************************************************************************************

  do {
    char *Current_Char_Address = strchr(Alphabet, Tape[head]);
    int  Current_Char_Index    = (int)(Current_Char_Address - Alphabet);
    int  Rules_Row             = ((Current_State * alphabet_size) + Current_Char_Index) * 3;

    fwrite(&Tape[490], 1, 80, stdout); printf("\n");
    for (int i = 0; i < head - 490; i++ ) printf(" ");
    printf( "^\n" );

    Current_Char_Index     = Rules_ptr[Rules_Row + 1];
    if (Current_Char_Index != SKIP) Tape[head] = Alphabet[Current_Char_Index];

    head = head + Rules_ptr[Rules_Row + 0];

    Current_State = Rules_ptr[Rules_Row + 2];

  } while ( Current_State > ERROR );

  fwrite(&Tape[490], 1, 80, stdout); printf("\n");
  for (int i = 0; i < head - 490; i++ ) printf(" ");
  if (free_Problem_Data) free(Problem_Data_ptr);
  if (free_Rules)        free(Rules_ptr);

  printf( "^\n DONE - %s\n", (Current_State == HALT) ? "Sucessfully" : "Error State" );

  return Current_State;
}

