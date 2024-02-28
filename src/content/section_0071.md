# Section 71

Here is a procedure that asks the user to type a line of input, assuming that the *selector* setting is either *TERM_ONLY* or *TERM_AND_LOG*.
The input is placed into locations *first* through *last − 1* of the *buffer* array, and echoed on the transcript file if appropriate.


```c include/io.h
// prints a string and gets a line of input
#define prompt_input(X) print((X)); term_input()
```

```c io/terminal.c
// << Start file |terminal.c| >>

// gets a line from the terminal
void term_input() {
    int k; // index into |buffer|
    update_terminal; // now the user sees the prompt for sure
    if (!input_ln(stdin)) {
        fatal_error("End of file on the terminal");
    }
    term_offset = 0; // the user's line ended with <return>
    decr(selector); // prepare to echo the input
    if (last != first) {
        for(k = first; k < last; k++) {
            print_strnumber(buffer[k]);
        }
    }
    print_ln();
    incr(selector); // restore previous status
}
```
