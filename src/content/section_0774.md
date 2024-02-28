# Section 774

When `\halign` or `\valign` has been scanned in an appropriate mode, $\TeX$ calls *init_align*, whose task is to get everything off to a good start.
This mostly involves scanning the preamble and putting its information into the preamble list.

```c alignment.c
// << Declare the procedure called |get_preamble_token| >>

void init_align() {
    pointer save_cs_ptr; // |warning_index| value for error messages
    pointer p;           // for short-term temporary use

    save_cs_ptr = cur_cs; // \halign or \valign, usually
    push_alignment();
    align_state = -1000000; // enter a new alignment level

    // << Check for improper alignment in displayed math >>
    
    push_nest(); // enter a new semantic level
    
    // << Change current mode to |-VMODE| for \halign, |-HMODE| for \valign >>
    
    scan_spec(ALIGN_GROUP, false);
    
    // << Scan the preamble and record it in the |preamble| list >>
    
    new_save_level(ALIGN_GROUP);
    if (every_cr != null) {
        begin_token_list(every_cr, EVERY_CR_TEXT);
    }
    align_peek(); // look for \noalign or \omit
}
```
