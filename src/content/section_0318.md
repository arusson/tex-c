# Section 318

But the trick is distracting us from our current goal, which is to understand the input state.
So let's concentrate on the data structures that are being pseudoprinted as we finish up the *show_context* procedure.

```c << Pseudoprint the line >>=
begin_pseudoprint;
if (buffer[limit] == end_line_char) {
    j = limit;
}
else {
    j = limit + 1; // determine the effective end of the line
}
if (j > 0) {
    for(i = start; i < j; i++) {
        if (i == loc) {
            set_trick_count;
        }
        print_strnumber(buffer[i]);
    }
}
```
