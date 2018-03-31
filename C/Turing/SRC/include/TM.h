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

