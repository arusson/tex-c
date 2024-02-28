# Section 207: The command codes

Before we can go any further, we need to define symbolic names for the internal code numbers that represent the various commands obeyed by $\TeX$.
These codes are somewhat arbitrary, but not completely so.
For example, the command codes for character types are fixed by the language, since a user says, e.g., '``\catcode `\$ = 3``' make `$` a math delimiter, and the command code *MATH_SHIFT* is equal to 3.
Some other codes have been made adjacent so that **case** statements in the program need not consider cases that are widely spaced, or so that **case** statements can be replaced by **if** statements.

At any rate, here is the list, for future reference.
First come the "catcode" commands, several of which share their numeric codes with ordinary commands when the catcode cannot emerge from $\TeX$'s scanning routine.

```c include/constants.h
#define ESCAPE        0  // escape delimiter (called \ in The TeXbook)
#define RELAX         0  // do nothing (\relax)
#define LEFT_BRACE    1  // beginning of a group ({)
#define RIGHT_BRACE   2  // ending of a group (})
#define MATH_SHIFT    3  // mathematics shift character ($)
#define TAB_MARK      4  // alignment delimiter (&, \span)
#define CAR_RET       5  // end of line (CARRIAGE_RETURN, \cr, \crcr)
#define OUT_PARAM     5  // output a macro parameter
#define MAC_PARAM     6  // macro parameter symbol (#)
#define SUP_MARK      7  // superscript (^)
#define SUB_MARK      8  // subscript (_)
#define IGNORE        9  // characters to ignore (^^@)
#define ENDV          9  // end of <v_j> list in alignment template
#define SPACER        10 // characters equivalent to blank space ( )
#define LETTER        11 // characters regarded as letters (A..Z, a..z})
#define OTHER_CHAR    12 // none of the special character types
#define ACTIVE_CHAR   13 // characters that invoke macros (~)
#define PAR_END       13 // end of paragraph (\par)
#define MATCH         13 // match a macro parameter
#define COMMENT       14 // characters that introduce comments (%)
#define END_MATCH     14 // end of parameters to macro
#define STOP          14 // end of job (\end, \dump)
#define INVALID_CHAR  15 // characters that shouldn't appear (^^?)
#define DELIM_NUM     15 // specify delimiter numerically (\delimiter)
#define MAX_CHAR_CODE 15 // largest catcode for individual characters
```
