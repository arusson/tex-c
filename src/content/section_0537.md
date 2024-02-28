# Section 537

Let's turn now to the procedure that is used to initiate file reading when an '`\input`' command is being processed.
Beware: For historic reasons, this code foolishly conserves a tiny bit of string pool space; but that can confuse the interactive '`E`' option.

> ![NOTE]
> Recall the '`E`' option is not supported in this implementation.

```c parser/filenames.c
// TeX will \input something
void start_input() {
    scan_file_name(); // set |cur_name| to desired file name
    if (cur_ext == EMPTY_STRING) {
        cur_ext = TEX_EXT;
    }
    pack_cur_name;
    while(true) {
        begin_file_reading(); // set up |cur_file| and new level of input
        if (a_open_in(&cur_file)) {
            break; // Goto done
        }
        if (cur_area == EMPTY_STRING) {
            pack_file_name(cur_name, TEX_AREA, cur_ext);
            if (a_open_in(&cur_file)) {
                break; // Goto done
            }
        }
        end_file_reading(); // remove the level that didn't work
        prompt_file_name("input file name", TEX_EXT);
    }
    // done:
    name = make_name_string();
    if (job_name == 0) {
        job_name = cur_name;
        open_log_file();
    } // |open_log_file| doesn't |show_context|, so |limit| and |loc| needn't be set to meaningful values yet
    if (term_offset + length(name) > MAX_PRINT_LINE - 2) {
        print_ln();
    }
    else if (term_offset > 0 || file_offset > 0) {
        print_char(' ');
    }
    print_char('(');
    incr(open_parens);
    slow_print(name);
    update_terminal;
    state = NEW_LINE;
    if (name == str_ptr - 1) {
        // conserve string pool space (but see note above)
        flush_string;
        name = cur_name;
    }
    // << Read the first line of the new file >>
}
```
