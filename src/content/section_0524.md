# Section 524

Here is the only place we use *pack_buffered_name*.
This part of the program becomes active when a "virgin" $\TeX$ is trying to get going, just after the preliminary initialization, or when the user is substituting another format file by typing '`&`' after the initial '`**`' prompt.
The buffer contains the first line of input in *buffer[loc .. (last − 1)]*, where *loc* $<$ *last* and *buffer[loc]* $\ne$ '␣'.

```c io/dumping.c
bool open_fmt_file() {
    int j; // the first space after the format file name
    j = loc;
    if (buffer[loc] == '&') {
        incr(loc);
        j = loc;
        buffer[last] = ' ';
        while (buffer[j] != ' ') {
            incr(j);
        }
        pack_buffered_name(0, loc, j - 1); // try first without the system file area
        if (w_open_in(&fmt_file)) {
            goto found;
        }
        pack_buffered_name(FORMAT_AREA_LENGTH, loc, j - 1); // now try the system format file area
        if (w_open_in(&fmt_file)) {
            goto found;
        }
        wterm_ln("Sorry, I can't find that format; will try PLAIN.");
        update_terminal;
    }
    // now pull out all the stops: try for the system plain file
    pack_buffered_name(FORMAT_DEFAULT_LENGTH - FORMAT_EXT_LENGTH, 1, 0);
    if (!w_open_in(&fmt_file)) {
        wterm_ln("I can't find the PLAIN format file!");
        return false;
    }
found:
    loc = j;
    return true;
}
```
