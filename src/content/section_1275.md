# Section 1275

```c builder/independent.c
void open_or_close_in() {
    int c; // 1 for \openin, 0 for \closein
    int n; // stream number
    c = cur_chr;
    scan_four_bit_int();
    n = cur_val;
    if (read_open[n] != CLOSED) {
        a_close(read_file[n]);
        read_open[n] = CLOSED;
    }
    if (c != 0) {
        scan_optional_equals();
        scan_file_name();
        if (cur_ext == EMPTY_STRING) {
            cur_ext = TEX_EXT; // ".tex"
        }
        pack_cur_name;
        if (a_open_in(&read_file[n])) {
            read_open[n] = JUST_OPEN;
        }
    }
}
```
