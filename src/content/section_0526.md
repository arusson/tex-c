# Section 526

Now let's consider the "driver" routines by which $\TeX$ deals with file names in a system-independent manner.
First comes a procedure that looks for a file name in the input by calling *get_x_token* for the information.

```c parser/filenames.c
void scan_file_name() {
    name_in_progress = true;
    begin_name();
    // << Get the next non-blank non-call token >>
    while(true) {
        if (cur_cmd > OTHER_CHAR || cur_chr > 255) {
              // not a character
            back_input();
            break; // Goto done
        }
        if (!more_name(cur_chr)) {
            break; // Goto done
        }
        get_x_token();
    }
    // done:
    end_name();
    name_in_progress = false;
}
```
