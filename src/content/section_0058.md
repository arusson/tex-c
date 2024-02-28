# Section 58

The *print_char* procedure sends one character to the desired destination, using the *XCHR* array to map it into an external character compatible with *input_ln*.
All printing comes through *print_ln* or *print_char*.

```c io/basic_printing.c
// prints a single character
void print_char(ASCII_code s) {
    // Section 244 (first condition)
    if (s == new_line_char && selector < PSEUDO) {
        print_ln();
        return;
    }
    switch(selector) {
    case TERM_AND_LOG:
        wterm_char(XCHR[s]);
        incr(term_offset);
        if (term_offset == MAX_PRINT_LINE) {
            wterm_cr;
            term_offset = 0;
        }
        wlog_char(XCHR[s]);
        incr(file_offset);
        if (file_offset == MAX_PRINT_LINE) {
            wlog_cr;
            file_offset = 0;
        }
        break;

    case LOG_ONLY:
        wlog_char(XCHR[s]);
        incr(file_offset);
        if (file_offset == MAX_PRINT_LINE) {
            print_ln();
        }
        break;

    case TERM_ONLY:
        wterm_char(XCHR[s]);
        incr(term_offset);
        if (term_offset == MAX_PRINT_LINE) {
            print_ln();
        }
        break;
        
    case NO_PRINT:
        do_nothing;
        break;

    case PSEUDO:
        if (tally < trick_count) {
            trick_buf[tally % ERROR_LINE] = s;
        }
        break;

    case NEW_STRING:
        // we drop characters if the string space is full
        if (pool_ptr < POOL_SIZE) {
            append_char(s);
        }
        break;

    default:
        write_char(write_file[selector], XCHR[s]);
    }
    incr(tally);
}
```
