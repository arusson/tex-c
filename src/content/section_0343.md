# Section 343

```c << Input from external file, |goto restart| if no input found >>=
switch_lbl:
if (loc <= limit) {
    // current line not yet finished
    cur_chr = buffer[loc];
    incr(loc);
reswitch:
    cur_cmd = cat_code(cur_chr);
    // << Change state if necessary, and |goto switch| if the current character should be ignored, or |goto reswitch| if the current character changes to another >>
}
else {
    state = NEW_LINE;
    // << Move to next line of file, or |goto restart| if there is no next line, or |return| if a \read line has finished >>
    check_interrupt;
    goto switch_lbl;
}
```
