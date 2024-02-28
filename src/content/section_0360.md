# Section 360

All of the easy branches of *get_next* have now been taken care of.
There is one more branch.

```c include/parser.h
#define end_line_char_inactive (end_line_char < 0 || end_line_char > 255)
```

```c << Move to next line of file, or |goto restart| if there is no next line, or |return| if a \read line has finished >>=
if (name > 17) {
    // << Read next line of file into |buffer|, or |goto restart| if the file has ended >>
}
else {
    if (!terminal_input){
        // \read line has ended
        cur_cmd = 0;
        cur_chr = 0;
        return;
    }
    if (input_ptr > 0) {
        // text was inserted during error recovery
        end_file_reading();
        goto restart; // resume previous level
    }
    if (selector < LOG_ONLY) {
        open_log_file();
    }
    if (interaction > NONSTOP_MODE) {
        if (end_line_char_inactive) {
            incr(limit);
        }
        if (limit == start) {
            // previous line was empty
            print_nl("(Please type a command or say `\\end')");
        }
        print_ln();
        first = start;
        prompt_input("*"); // input on-line into |buffer|
        limit = last;
        if (end_line_char_inactive) {
            decr(limit);
        }
        else {
            buffer[limit] = end_line_char;
        }
        first = limit + 1;
        loc = start;
    }
    else {
        // nonstop mode, which is intended for overnight batch processing, never waits for on-line input
        fatal_error("*** (job aborted, no legal \\end found)");
    }
}
```
