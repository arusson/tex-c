# Section 534

The *open_log_file* routine is used to open the transcript file and to help it catch up to what has previously been printed on the terminal.

> ![NOTE]
> Strings `"texput"` and `".log"` are added in the pool.

```c << Read the other strings >>+=
put_string("texput"); // TEXPUT_STRING: 263
put_string(".log");   // LOG_EXT: 264
```

```c << Internal strings numbers in the pool >>+=
#define TEXPUT_STRING 263
#define LOG_EXT       264
```

```c io/files.c
void open_log_file() {
    int old_setting; // previous |selector| setting
    int k;           // index into |months| and |buffer|
    int l;           // end of first input line
    char *months[12] = {
        "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
        "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
    }; // abbreviations of month names
    old_setting = selector;
    if (job_name == 0) {
        job_name = TEXPUT_STRING; // "texput"
    }
    pack_job_name(LOG_EXT);
    while (!a_open_out(&log_file)) {
        // << Try to get a different log file name >>
    }
    log_name = make_name_string();
    selector = LOG_ONLY;
    log_opened = true;
    // << Print the banner line, including the date and time >>
    input_stack[input_ptr] = cur_input; // make sure bottom level is in memory
    print_nl("**");
    l = input_stack[0].limit_field; // last position of first line
    if (buffer[l] == end_line_char) {
        decr(l);
    }
    for(k = 1; k <= l; k++) {
        print_strnumber(buffer[k]);
    }
    print_ln(); // now the transcript file contains the first line of input
    selector = old_setting + 2; // |LOG_ONLY| or |TERM_AND_LOG|
}
```
