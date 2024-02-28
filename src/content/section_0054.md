# Section 54: On-line and off-line printing

Messages that are sent to a user's terminal and to the transcript-log file are produced by several *'print'* procedures. These procedures will direct their output to a variety of places, based on the setting of the global variable *selector*, which has the following possible values:

- *TERM_AND_LOG*, the normal setting, prints on the terminal and on the transcript file.
- *LOG_ONLY*, prints only on the transcript file.
- *TERM_ONLY*, prints only on the terminal.
- *NO_PRINT*, doesn't print at all. This is used only in rare cases before the transcript file is open.
- *PSEUDO*, puts output into a cyclic buffer that is used by the *show_context* routine; when we get to that routine we shall discuss the reasoning behind this curious mode.
- *NEW_STRING*, appends the output to the current string in the string pool.
- 0 to 15, prints on one of the sixteen files for `\write` output.

The symbolic names *'TERM_AND_LOG'*, etc., have been assigned numeric codes that satisfy the convenient relations *NO_PRINT + 1 = TERM_ONLY*, *NO_PRINT + 2 = LOG_ONLY*, *TERM_ONLY + 2 = LOG_ONLY + 1 = TERM_AND_LOG*.

Three additional global variables, *tally* and *term_offset* and *file_offset*, record the number of characters that have been printed since they were most recently cleared to zero.
We use *tally* to record the length of (possibly very long) stretches of printing; *term_offset* and *file_offset*, on the other hand, keep track of how many characters have appeared so far on the current line that has been output to the terminal or to the transcript file, respectively.

```c include/constants.h
#define NO_PRINT     16 // |selector| setting that makes data disappear
#define TERM_ONLY    17 // printing is destined for the terminal only
#define LOG_ONLY     18 // printing is destined for the transcript file only
#define TERM_AND_LOG 19 // normal |selector| setting
#define PSEUDO       20 // special |selector| setting for |show_context|
#define NEW_STRING   21 // printing is deflected to the string pool
#define MAX_SELECTOR 21 // highest selector setting
```

```c << Global variables >>+=
alpha_file log_file;                  // transcript of TeX session
int selector;                         // where to print a message
unsigned char dig[23];                // digits in a number being output
int tally;                            // the number of characters recently printed
int term_offset;                      // the number of characters on the current terminal line
int file_offset;                      // the number of characters on the current file line
ASCII_code trick_buf[ERROR_LINE + 1]; // circular buffer for pseudoprinting
int trick_count;                      // threshold for pseudoprinting, explained later
int first_count;                      // another variable for pseudoprinting
```
