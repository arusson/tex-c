# Section 303

Let's look more closely now at the control variables (*state*,&nbsp;*index*,&nbsp;*start*,&nbsp;*loc*,&nbsp;*limit*,&nbsp;*name*), assuming that $\TeX$ is reading a line of characters that have been input from some file or from the user's terminal.
There is an array called *buffer* that acts as a stack of all lines of characters that are currently being read from files, including all lines on subsidiary levels of the input stack that are not yet completed.
$\TeX$ will return to the other lines when it is finished with the present input file.

(Incidentally, on a machine with byte-oriented addressing, it might be appropriate to combine *buffer* with the *str_pool* array, letting the buffer entries grow downward from the top of the string pool and checking that these two tables don't bump into each other.)

The line we are currently working on begins in position *start* of the buffer;
the next character we are about to read is *buffer[loc]*;
and *limit* is the location of the last character present.
If *loc* $>$ *limit*, the line has been completely read.
Usually *buffer[limit]* is the *end_line_char*, denoting the end of a line, but this is not true if the current line is an insertion that was entered on the user's terminal in response to an error message.

The *name* variable is a string number that designates the name of the current file, if we are reading a text file.
It is zero if we are reading from the terminal; it is *n + 1* if we are reading from input stream *n*, where *0* $\leq$ *n* $\leq$ *16*.
(Input stream 16 stands for an invalid stream number; in such cases the input is actually from the terminal, under control of the procedure *read_toks*.)

The *state* variable has one of three values, when we are scanning such files:

1. *state = MID_LINE* is the normal state.
2. *state = SKIP_BLANKS* is like *MID_LINE*, but blanks are ignored.
3. *state = NEW_LINE* is the state at the beginning of a line.

These state values are assigned numeric codes so that if we add the state code to the next character's command code, we get distinct values.
For example, *'MID_LINE + SPACER'* stands for the case that a blank space character occurs in the middle of a line when it is not being ignored; after this case is processed, the next value of *state* will be *SKIP_BLANKS*.

```c include/constants.h
#define MID_LINE    1                                   // |state| code when scanning a line of characters
#define SKIP_BLANKS (2 + MAX_CHAR_CODE)                 // |state| code when ignoring blanks
#define NEW_LINE    (3 + MAX_CHAR_CODE + MAX_CHAR_CODE) // |state| code at start of line
```
