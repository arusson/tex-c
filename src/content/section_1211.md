# Section 1211

If the user says, e.g., '`\global\global`', the redundancy is silently accepted.

```c builder/independent.c
// << Start file |independent.c| >>

// << Declare subprocedures for |prefixed_command| >>

void prefixed_command() {
    small_number a;         // accumulated prefix codes so far
    internal_font_number f; // identifies a font
    halfword j;             // index into a \parshape specification
    int k;                  // index into |font_info|
    pointer p, q;           // for temporary short - term use
    int n;                  // ditto
    bool e;                 // should a definition be expanded? or was \let not done?
    
    a = 0;
    while (cur_cmd == PREFIX) {
        if (!odd(a / cur_chr)) {
            a += cur_chr;
        }
        // << Get the next non-blank non-relax non-call token >>
        if (cur_cmd <= MAX_NON_PREFIXED_COMMAND) {
            // << Discard erroneous prefixes and |return| >>
        }
    }
    // << Discard the prefixes \long and \outer if they are irrelevant >>
    // << Adjust for the setting of \globaldefs >>
    switch (cur_cmd) {
    // << Assignments >>
    
    default:
        confusion("prefix");
    }
done:
    // << Insert a token saved by \afterassignment, if any >>
}
```
