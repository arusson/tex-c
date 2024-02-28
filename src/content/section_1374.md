# Section 1374

We don't implement `\write` inside of leaders.
(The reason is that the number of times a leader box appears might be different in different implementations, due to machine-dependent rounding in the glue calculations.)

```c << Do some work that has been queued up for \write >>=
if (!doing_leaders) {
    j = write_stream(p);
    if (subtype(p) == WRITE_NODE) {
        write_out(p);
    }
    else {
        if (write_open[j]) {
            a_close(write_file[j]);
        }
        if (subtype(p) == CLOSE_NODE) {
            write_open[j] = false;
        }
        else if (j < 16) {
            cur_name = open_name(p);
            cur_area = open_area(p);
            cur_ext = open_ext(p);
            if (cur_ext == EMPTY_STRING) {
                cur_ext = TEX_EXT; // ".tex"
            }
            pack_cur_name;
            while (!a_open_out(&write_file[j])) {
                prompt_file_name("output file name", TEX_EXT);
            }
            write_open[j] = true;
        }
    }
}
```
