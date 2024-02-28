# Section 362

```c << Read next line of file into |buffer|, or |goto restart| if the file has ended >>=
incr(line);
first = start;
if (!force_eof) {
    if (input_ln(cur_file)) {
        // not end of file
        firm_up_the_line(); // this sets |limit|
    }
    else {
        force_eof = true;
    }
}
if (force_eof) {
    print_char(')');
    decr(open_parens);
    update_terminal; // show user that file has been read
    force_eof = false;
    end_file_reading(); // resume previous level
    check_outer_validity();
    goto restart;
}
if (end_line_char_inactive) {
    decr(limit);
}
else {
    buffer[limit] = end_line_char;
}
first = limit + 1;
loc = start; // ready to read
```
