# Section 815

Since *line_break* is a rather lengthy procedure---sort of a small world unto itself---we must build it up little by little, somewhat more cautiously than we have done with the simpler procedures of $\TeX$.
Here is the general outline.

```c breaker/line_break.c
// << Start file |line_break.c| >>

// << Declare subprocedures for |line_break| >>

void line_break(int final_widow_penalty) {
    // << Local variables for line breaking >>
    pack_begin_line = mode_line; // this is for over/underfull box messages

    // << Get ready to start line breaking >>

    // << Find optimal breakpoints >>
    
    // << Break the paragraph at the chosen breakpoints, justify the resulting lines to the correct widths, and append them to the current vertical list >>
    
    // << Clean up the memory by removing the break nodes >>
    pack_begin_line = 0;
}
```
