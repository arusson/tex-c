# Section 638

The *hlist_out* and *vlist_out* procedures are now complete, so we are ready for the *ship_out* routine that gets them started in the first place.

```c dvi.c
// output the box |p|
void ship_out(pointer p) {
    int page_loc;    // location of the current |BOP|
    int j, k;        // indices to first ten count registers
    pool_pointer s;  // index into |str_pool|
    int old_setting; // saved |selector| setting
    
    if (tracing_output > 0) {
        print_nl("");
        print_ln();
        print("Completed box being shipped out");
    }
    if (term_offset > MAX_PRINT_LINE - 9) {
        print_ln();
    }
    else if (term_offset > 0 || file_offset > 0) {
        print_char(' ');
    }
    print_char('[');
    j = 9;
    while (count(j) == 0 && j > 0) {
        decr(j);
    }
    for(k = 0; k <= j; k++) {
        print_int(count(k));
        if (k < j) {
            print_char('.');
        }
    }
    update_terminal;
    if (tracing_output > 0) {
        print_char(']');
        begin_diagnostic();
        show_box(p);
        end_diagnostic(true);
    }
    // << Ship box |p| out >>
    if (tracing_output <= 0) {
        print_char(']');
    }
    dead_cycles = 0;
    update_terminal; // progress report
    // << Flush the box from memory, showing statistics if requested >>
}
```
