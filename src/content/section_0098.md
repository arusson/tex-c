# Section 98

When an interrupt has been detected, the program goes into its highest interaction level and lets the user have nearly the full flexibility of the *error* routine.
$\TeX$ checks for interrupts only at times when it is safe to do this.

```c error.c
void pause_for_instructions() {
    if (ok_to_interrupt) {
        interaction = ERROR_STOP_MODE;
        if (selector == LOG_ONLY || selector == NO_PRINT) {
            incr(selector);
        }
        print_err("Interruption");
        help3("You rang?")
            ("Try to insert an instruction for me (e.g. `I\\showlists'),")
            ("unless you just want to quit by typing `X'.");
        deletions_allowed = false;
        error();
        deletions_allowed = true;
        interrupt = 0;
    }
}
```
