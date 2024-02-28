# Section 1337

When we begin the following code, $\TeX$'s tables may still contain garbage;
the strings might not even be present.
Thus we must proceed cautiously to get bootstrapped in.

But when we finish this part of the program, $\TeX$ is ready to call on the *main_control* routine to do its work.

```c << Get the first line of input and prepare to start >>=
// << Initialize the input routines >>
if (format_ident == 0 || buffer[loc] == '&') {
    if (format_ident != 0) {
        initialize(); // erase preloaded format
    }
    if (!open_fmt_file()) {
        exit(0);
    }
    if (!load_fmt_file()) {
        w_close(fmt_file);
        exit(0);
    }
    w_close(fmt_file);
    while (loc < limit && buffer[loc] == ' ') {
        incr(loc);
    }
}
if (end_line_char_inactive) {
    decr(limit);
}
else {
    buffer[limit] = end_line_char;
}
fix_date_and_time();
// << Initialize the print |selector| based on |interaction| >>
if (loc < limit && cat_code(buffer[loc]) != ESCAPE) {
    // \input assumed
    start_input();
}
```
