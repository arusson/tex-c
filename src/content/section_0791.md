# Section 791

When the *ENDV* command at the end of a $\langle v_j\rangle$ template comes through the
scanner, things really start to happen; and it is the *fin_col* routine that makes them happen.
This routine returns *true* if a row as well as a column has been finished.

```c alignment.c
bool fin_col() {
    pointer p;    // the alignrecord after the current one
    pointer q, r; // temporary pointers for list manipulation
    pointer s;    // a new span node
    pointer u;    // a new unset box
    scaled w;     // natural width
    int o;        // order of infinity
    halfword n;   // span counter
    
    if (cur_align == null) {
        confusion("endv");
    }
    q = link(cur_align);
    if (q == null) {
        confusion("endv");
    }
    
    if (align_state < 500000) {
        fatal_error("(interwoven alignment preambles are not allowed)");
    }
    p = link(q);
    // << If the preamble list has been traversed, check that the row has ended >>
    if (extra_info(cur_align) != SPAN_CODE) {
        unsave();
        new_save_level(ALIGN_GROUP);
        // << Package an unset box for the current column and record its width >>
        // << Copy the tabskip glue between columns >>
        if (extra_info(cur_align) >= CR_CODE) {
            return true;
        }
        init_span(p);
    }
    align_state = 1000000;
    // << Get the next non-blank non-call token >>
    cur_align = p;
    init_col();
    return false;
}
```
