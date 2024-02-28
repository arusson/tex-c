# Section 57

To end a line of text output, we call *print_ln*.

```c io/basic_printing.c
// << Start file |basic_printing.c| >>

// prints an end-of-line
void print_ln() {
    switch(selector) {
    case TERM_AND_LOG:
        wterm_cr;
        wlog_cr;
        term_offset = 0;
        file_offset = 0;
        break;
    
    case LOG_ONLY:
        wlog_cr;
        file_offset = 0;
        break;

    case TERM_ONLY:
        wterm_cr;
        term_offset = 0;
        break;
    
    case NO_PRINT:
    case PSEUDO:
    case NEW_STRING:
        do_nothing;
        break;
    
    default:
        write_ln(write_file[selector], "");
    }
    // |tally| is not affected
}
```
