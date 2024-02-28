# Section 31

The *input_ln* function brings the next line of input from the specified file into available positions of the buffer array and returns the value *true*, unless the file has already been entirely read, in which case it returns *false* and sets *last &larr; first*.
In general, the *ASCII_code* numbers that represent the next line of the file are input into
*buffer[first]*, *buffer[first + 1]*, $\ldots$, *buffer[last − 1]*;
and the global variable *last* is set equal to *first* plus the length of the line.
Trailing blanks are removed from the line; thus, either *last = first* (in which case the line was entirely blank) or *buffer[last − 1]* $\ne$ '␣'.

An overflow error is given, however, if the normal actions of *input_ln* would make *last* $\geq$ *BUF_SIZE*;
this is done so that other parts of $\TeX$ can safely look at the contents of *buffer[last + 1]* without overstepping the bounds of the *buffer* array.
Upon entry to *input_ln*, the condition *first < BUF_SIZE* will always hold, so that there is always room for an "empty" line.

The variable *max_buf_stack*, which is used to keep track of how large the *BUF_SIZE* parameter must be to accommodate the present job, is also kept up to date by *input_ln*.

If the *bypass_eoln* parameter is *true*, *input_ln* will do a *get* before looking at the first character of the line; this skips over an *eoln* that was in *f↑*.
The procedure does not do a *get* when it reaches the end of the line; therefore it can be used to acquire input from the user's terminal as well as from ordinary text files.

Standard Pascal says that a file should have *eoln* immediately before *eof*, but $\TeX$ needs only a weaker restriction:
If *eof* occurs in the middle of a line, the system function *eoln* should return a *true* result (even though *f↑* will be undefined).

Since the inner loop of *input_ln* is part of $\TeX$'s "inner loop"---each character of input comes in at this place---it is wise to reduce system overhead by making use of special routines that read in an entire array of characters at once, if such routines are available.
The following code uses standard Pascal to illustrate what needs to be done, but finer tuning is often possible at well-developed Pascal sites.

> ![NOTE]
> The `bypass_eoln` boolean has been removed.

```c io/files.c
// inputs the next line or returns |false|
int input_ln(alpha_file f) {
    int last_nonblank; // |last| with trailing blanks removed
    int c;

    last = first;
    last_nonblank = first;
    while ((c = fgetc(f)) != '\n' && c != EOF) {
        if (last >= max_buf_stack) {
            max_buf_stack = last + 1;
            if (max_buf_stack == BUF_SIZE) {
                // << Report overflow of the input buffer, and abort >>
            }
        }
        buffer[last] = XORD[c];
        incr(last);
        if (buffer[last - 1] != ' ') {
            last_nonblank = last;
        }
    }
    if (c == EOF && last == first) {
        return false;
    }
    last = last_nonblank;
    return true;
}
```