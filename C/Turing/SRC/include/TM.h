/* Includes needed by this program that are not in DPJ.h
*/

#include <unistd.h>
#include <stdint.h>    // Not needed currently, but maybe if I try strcspn
                       // to find chars in Alphabet (see Notes.txt).
#include <string.h>

#include <readline/readline.h>  // Needed for readline(), not currently used here
#include <readline/history.h>   // Probably move to DPJ.h eventually.

/* Defines specific to this program */

#define MODLINE      20     // Modest line length of a problem file.
                            // Start size of Line Buffer for getline().
                            // Will be increased as required by getline().

#define INFINITE     1000
#define EMPTY        '~'
#define STARTHEAD    INFINITE/2

#define ALPHABET     "01~"
#define SKIP         -1

#define PROBLEMDATA  "0000000000000000000000000000000000"
#define STARTPROBLEM STARTHEAD

#define LEFT         -1
#define HOLD         0
#define RIGHT        1

#define HALT         0   // Define mandatory HALT  State as first  State
#define ERROR        1   // Define mandatory ERROR State as second State
#define START        2   // Define mandatory START State as third State
#define STATECOUNT   6
#define RULES        HALT,HALT,HALT,HALT,HALT,HALT,HALT,HALT,HALT,\
                     ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,\
                     RIGHT,SKIP,3,RIGHT,SKIP,3,HOLD,SKIP,ERROR,\
                     RIGHT,SKIP,3,RIGHT,SKIP,3,LEFT,SKIP,4,\
                     HOLD,1,5,LEFT,0,4,HOLD,1,HALT,\
                     LEFT,SKIP,5,LEFT,SKIP,5,RIGHT,SKIP,HALT

/* Functions specific to this program */

int Read_Problem_File(char *Problem_Filename, int *infinite, int *start_head,
                      char **Problem_Data, int *start_data, int *free_Problem_Data,
                      char **Alphabet, int *alphabet_size, int *free_alphabet,
                      int *state_count, int *rules_size, int **Rules, int *free_Rules) {

  size_t  line_buffer_size    = MODLINE;
  char    *raw_line_buffer    = malloc(line_buffer_size);
  ssize_t current_line_length = 0;

  FILE *Problem_File = fopen(Problem_Filename, "r");
  int line_count    = 0;

  while ( ( current_line_length = getline(&raw_line_buffer,
          &line_buffer_size, Problem_File ) ) != EOF ) {

    char *line_buffer = trimwhitespace(raw_line_buffer);

    line_count++;

    if ( ( line_buffer[0] == '#' ) || ( current_line_length == (ssize_t)1) ) continue;

    if ( strncmp(line_buffer, "--", (size_t)2 ) != STRMATCH) {
      char first_chars[3];
      memcpy( first_chars, &line_buffer[0], 2 ); first_chars[2] = '\0';
      sprintf(Error_prefix, "Line %d begins: \"%s\" - ", line_count, first_chars);
      Error(WARNING, Error_prefix, BADARG, "Line ignored");
      continue;
    }

    char *line_content         = trimwhitespace(&line_buffer[2]);
    char *delimiter            = " \n";
    char *first_token          = strtok(line_content, delimiter);

// Define a new maximum "infinite" tape length.

    if      ( strcmp(first_token, "infinite"   ) == STRMATCH ) {
      *infinite   = strtol( strtok(NULL, delimiter), NULL, 10 );
      printf("infinite %d\n",*infinite);
    }

// Specify initial position of tape head.

    else if ( strcmp(first_token, "start_head"       ) == STRMATCH ) {
      *start_head = strtol( strtok(NULL, delimiter), NULL, 10 );
      printf("start_head %d\n",*start_head);
    }

// Define a new position of data in the tape.

    else if ( strcmp(first_token, "start_data"       ) == STRMATCH ) {
      *start_data = strtol( strtok(NULL, delimiter), NULL, 10 );
      printf("start_data %d\n",*start_data);
    }

// Define new problem data.

    else if ( strcmp(first_token, "data"       ) == STRMATCH ) {
      char *argval       = strtok(NULL, delimiter);
      size_t data_length = strlen(argval);
      *Problem_Data      = malloc(data_length * sizeof(char) ); *free_Problem_Data = TRUE;
      strncpy(*Problem_Data, argval, data_length);
      printf("data %s\n", *Problem_Data);
    }

// Define a new Alphabet.
// Must be done BEFORE defnition of problem Rules as
// memory requirement for Rules is dependent upon length of
// Alaphabet. NO CHECKING OF DEFINITION ORDER IS ATTEMPTED.

    else if ( strcmp(first_token, "alphabet"  ) == STRMATCH ) {
      char *argval       = strtok(NULL, delimiter);
      *alphabet_size     = (int)strlen(argval);
      *Alphabet          = malloc( (*alphabet_size) * sizeof(char) ); *free_alphabet = TRUE;
      strcpy(*Alphabet, argval);
      printf("alphabet %s %d\n", *Alphabet, *alphabet_size);
    }

// Define a new problem Rules.
// Must be done AFTER defnition of Alphabet as
// memory requirement for Rules is dependent upon length of
// Alaphabet. NO CHECKING OF DEFINITION ORDER IS ATTEMPTED.

    else if ( strcmp(first_token, "rules"     ) == STRMATCH ) {
      *state_count = strtol( strtok(NULL, delimiter), NULL, 10 );
      *rules_size  = (*alphabet_size) * (*state_count) * 3;
      *Rules       = (int *)malloc( (*rules_size) * sizeof(int) ); *free_Rules = TRUE;
      int *rule;
      for (rule = *Rules; ( (rule - *Rules) < *rules_size ); rule++)
        *rule = (int)strtol( strtok(NULL, delimiter), NULL, 10 );
      printf("rules \n");
      for (rule = *Rules; rule < (*Rules + *rules_size); rule++)
        printf("\t%d\t%c", *rule, !( (rule - *Rules + 1) % 3) ? '\n' : '-' );
    }

    else {
      sprintf(Error_prefix, "Line %d Arguement Type: \"%s\" - ", line_count, first_token );
      Error(WARNING, Error_prefix,UNKARG,"Arguement ignored");
    }

  }

  printf("Problem File  \"%s\" of %d lines read\n",Problem_Filename,line_count);

  free(raw_line_buffer);

  return 0;

}
