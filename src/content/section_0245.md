# Section 245

$\TeX$ is occasionally supposed to print diagnostic information that goes only into the transcript file, unless *tracing_online* is positive.
Here are two routines that adjust the destination of print commands:

```c io/other_printing.c
// prepare to do some tracing
void begin_diagnostic() {
    old_setting = selector;
    if (tracing_online <= 0 && selector == TERM_AND_LOG) {
        decr(selector);
        if (history == SPOTLESS) {
            history = WARNING_ISSUED;
        }
    }
}

// restore proper conditions after tracing
void end_diagnostic(bool blank_line) {
    print_nl("");
    if (blank_line) {
        print_ln();
    }
    selector = old_setting;
}
```
