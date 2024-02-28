# Section 30

Input from text files is read one line at a time, using a routine called *input_ln*.
This function is defined in terms of global variables called *buffer*, *first*, and *last* that will be described in detail later; for now, it suffices for us to know that *buffer* is an array of *ASCII_code* values, and that *first* and *last* are indices into this array representing the beginning and ending of a line of text.

```c << Global variables >>+=
ASCII_code buffer[BUF_SIZE + 1]; // lines of character being read
int first;                       // the first unused position in |buffer|
int last;                        // end of the line just input to |buffer|
int max_buf_stack;               // largest index used in |buffer|
```
