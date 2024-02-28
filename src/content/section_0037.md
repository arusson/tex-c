# Section 37

The following program does the required initialization without retrieving a possible command line.
It should be clear how to modify this routine to deal with command lines, if the system permits them.

> ![NOTE]
> This procedure is adapted so the arguments of the command line are copied into *buffer* one by one (a single space is added between arguments).
> This copy is based on *input_ln*, and the code that follows issue the original loop of *init_terminal*:
> Then, *buffer[loc]* will point to the first nonblank character of the commande line (in case the user typed `tex " paper.tex"` for example), and *buffer[last − 1]* to the last nonblank character.
> In case the input filename has not been provided, then we fall back into the original code using the *input_ln* function with *stdin* as input (with interverted code to avoid a call to *input_ln* if the command line was not empty).

```c init_cleanup.c
// gets the terminal input started
bool init_terminal(int argc, char *argv[]) {
    int last_nonblank; // |last| with trailing blanks removed
    int i; // index into |argv|
    int j; // indox into an argument of |argv|
    int n; // length of an argument

    // The code below does the same thing as |input_ln|
    last = first;
    last_nonblank = first;
    for(i = 1; i < argc; i++) {
        n = strlen(argv[i]);
        if (last >= max_buf_stack) {
            max_buf_stack = last + n + 1; // a single space is added between arguments
            if (max_buf_stack >= BUF_SIZE) {
                // << Report overflow of the input buffer, and abort >>
            }
        }
        for(j = 0; j < n; j++) {
            buffer[last] = XORD[(int)argv[i][j]];
            incr(last);
            if (buffer[last - 1] != ' ') {
                last_nonblank = last;
            }
        }
        buffer[last] = ' ';
        incr(last);
    }
    last = last_nonblank;
    
    // the (adapted) original loop
    while (true) {
        loc = first;
        while (loc < last && buffer[loc] == ' ') {
            incr(loc);
        }
        if (loc < last) {
            return true;
        }
        printf("Please type the name of your input file.\n");
        printf("**");
        update_terminal;
        if (!input_ln(stdin)) {
            // this should'nt happen
            printf("\n!End of file on the terminal... why?");
            return false;
        }
    }
}
```