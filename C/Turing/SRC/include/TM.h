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
#define STARTPROBLEM INFINITE/2
#define EMPTY        '~'

#define MAXSTATES    50

#define ALPHABET     "01~"
#define SKIP         -1
#define PROBLEMDATA  "0000000000000000000000000000000000"

#define LEFT         -1
#define HOLD         0
#define RIGHT        1

#define HALT         0   // Define mandatory HALT  State as first  State
#define ERROR        1   // Define mandatory ERROR State as second State
#define START        2   // Define mandatory START State as third State
#define RULES        {HALT,HALT,HALT},{HALT,HALT,HALT},{HALT,HALT,HALT},\
                     {ERROR,ERROR,ERROR},{ERROR,ERROR,ERROR},{ERROR,ERROR,ERROR},\
                     {RIGHT,SKIP,3},{RIGHT,SKIP,3},{HOLD,SKIP,ERROR},\
                     {RIGHT,SKIP,3},{RIGHT,SKIP,3},{LEFT,SKIP,4},\
                     {HOLD,1,5},{LEFT,0,4},{HOLD,1,HALT},\
                     {LEFT,SKIP,5},{LEFT,SKIP,5},{RIGHT,SKIP,HALT}

/* Functions specific to this program */

int Read_Problem_File(char *Problem_Filename, int *infinite, char **Problem_Data,
                      int  **Rules) {

  size_t  line_buffer_size    = MODLINE;
  char    *line_buffer        = malloc(line_buffer_size);
  ssize_t current_line_length = 0;

  FILE *Problem_File = fopen(Problem_Filename, "r");
  int line_count = 0;

  while ( ( current_line_length = getline(&line_buffer,
          &line_buffer_size, Problem_File ) ) != EOF ) {

    line_count++;

    if ( ( line_buffer[0] == '#' ) || ( current_line_length == (ssize_t)1) ) continue;

    if ( strncmp(line_buffer, "--", (size_t)2 ) != STRMATCH) {
      char first_chars[3];
      memcpy( first_chars, &line_buffer[0], 2 ); first_chars[2] = '\0';
      sprintf(Error_prefix, "Line %d begins: \"%s\" - ", line_count, first_chars);
      Error(WARNING, Error_prefix, BADARG, "Line ignored");
    }

    char *line_content = &line_buffer[2];
    char *delimiter    = " \n";
    while ( line_content[0] == delimiter[0] ) line_content++;
    char *first_token  = strtok(line_content, delimiter);
    line_content += strlen(first_token); while ( line_content[0] == delimiter[0] ) line_content++;
    if      ( strcmp(first_token, "infinite"   ) == STRMATCH ) {
      char *argval = strtok(NULL, delimiter);
      *infinite = strtol(argval, NULL, 10);
      printf("infinite %d\n",*infinite);
    }
    else if ( strcmp(first_token, "data"       ) == STRMATCH ) {
      char *argval       = strtok(NULL, delimiter);
      size_t data_length = strlen(argval);
      printf("'''''''%s'''''''''\n",*Problem_Data);
      *Problem_Data      = malloc(data_length);
      strncpy(*Problem_Data, argval, data_length);
      printf("data %s\n", *Problem_Data);
    }
    else if ( strcmp(first_token, "data_start") == STRMATCH ) {
      printf("data_start\n");
    }
    else if ( strcmp(first_token, "head_init" ) == STRMATCH ) {
      printf("head_init\n");
    }
    else if ( strcmp(first_token, "alphabet"  ) == STRMATCH ) {
      printf("alphabet\n");
    }
    else if ( strcmp(first_token, "rules"     ) == STRMATCH ) {
      printf("rules\n");
    }
    else {
      sprintf(Error_prefix, "Line %d Arguement Type: \"%s\" - ", line_count, first_token );
      Error(WARNING, Error_prefix,UNKARG,"Arguement ignored");
    }

  }

  printf("Problem File  \"%s\" of %d lines read\n",Problem_Filename,line_count);
  return 0;

}
