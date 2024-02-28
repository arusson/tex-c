# Section 304

Additional information about the current line is available via the *index* variable, which counts how many lines of characters are present in the buffer below the current level.
We have *index = 0* when reading from the terminal and prompting the user for each line; then if the user types, e.g., '`\input paper`', we will have *index = 1* while reading the file `paper.tex`.
However, it does not follow that *index* is the same as the input stack pointer, since many of the levels on the input stack may come from token lists.
For example, the instruction '`\input paper`' might occur in a token list.

The global variable *in_open* is equal to the *index* value of the highest non-token-list level.
Thus, the number of partially read lines in the buffer is *in_open + 1*, and we have *in_open = index* when we are not reading a token list.

If we are not currently reading from the terminal, or from an input stream, we are reading from the file variable *input_file[index]*.
We use the notation *terminal_input* as a convenient abbreviation for *name = 0*, and *cur_file* as an abbreviation for *input_file[index]*.

The global variable *line* contains the line number in the topmost open file, for use in error messages.
If we are not reading from the terminal, *line_stack[index]* holds the line number for the
enclosing level, so that *line* can be restored when the current file has been read.
Line numbers should never be negative, since the negative of the current line number is used to identify the user's output routine in the *mode_line* field of the semantic nest entries.

If more information about the input state is needed, it can be included in small arrays like those shown here.
For example, the current page or segment number in the input file might be put into a variable *page*, maintained for enclosing levels in *'page_stack:* **array** *[1 .. MAX_IN_OPEN]* **of** *integer'* by analogy with *line_stack*.

> ![NOTE]
> *input_file* and *line_stack* are indexed from 1, so pointer arithmetic again.

```c include/datastructures.h
#define terminal_input (name == 0)       // are we reading from the terminal?
#define cur_file       input_file[index] // the current |alpha_file| variable
```

```c << Global variables >>+=
int in_open;     // the number of lines in the buffer, less one
int open_parens; // the number of open text files
alpha_file input_file0[MAX_IN_OPEN];
alpha_file *input_file = input_file0 - 1;
int line; // current line number in the current source file
int line_stack0[MAX_IN_OPEN];
int *line_stack = line_stack0 - 1;
```
