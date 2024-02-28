# Section 306

Here is a procedure that uses *scanner_status* to print a warning message when a subfile has ended, and at certain other crucial times:

```c datastructures/stack.c
void runaway() {
    pointer p = null; // head of runaway list
    if (scanner_status > SKIPPING) {
        print_nl("Runaway ");
        switch (scanner_status) {
        case DEFINING:
            print("definition");
            p = def_ref;
            break;
        
        case MATCHING:
            print("argument");
            p = TEMP_HEAD;
            break;
        
        case ALIGNING:
            print("preamble");
            p = HOLD_HEAD;
            break;
        
        case ABSORBING:
            print("text");
            p = def_ref;
        } // there are no other cases
        print_char('?');
        print_ln();
        show_token_list(link(p), null, ERROR_LINE - 10);
    }
}
```
