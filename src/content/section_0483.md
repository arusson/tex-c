# Section 483

```c << Input and store tokens from the next line of the file >>=
begin_file_reading();
name = m + 1;
if (read_open[m] == CLOSED) {
    // << Input for \read from the terminal >>
}
else if (read_open[m] == JUST_OPEN) {
    // << Input the first line of |read_file[m]| >>
}
else {
    // << Input the next line of |read_file[m]| >>
}
limit = last;
if (end_line_char_inactive) {
    decr(limit);
}
else {
    buffer[limit] = end_line_char;
}
first = limit + 1;
loc = start;
state = NEW_LINE;
while(true) {
    get_token();
    if (cur_tok == 0) {
        break; // Goto done
        // |cur_cmd == cur_chr == 0| will occur at the end of the line
    } 
    if (align_state < 1000000) {
        // unmatched '}' aborts the line
        do {
            get_token();
        } while (cur_tok != 0);
        align_state = 1000000;
        break; // Goto done
    }
    store_new_token(cur_tok);
}
// done:
end_file_reading();
```
