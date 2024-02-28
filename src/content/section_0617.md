# Section 617

```c << Initialize variables as |ship_out| begins >>=
dvi_h = 0;
dvi_v = 0;
cur_h = h_offset;
dvi_f = NULL_FONT;
ensure_dvi_open;
if (total_pages == 0) {
    dvi_out(PRE);
    dvi_out(ID_BYTE); // output the preamble
    dvi_four(25400000);
    dvi_four(473628672); // conversion ratio for sp
    prepare_mag();
    dvi_four(mag); // magnification factor is frozen
    old_setting = selector;
    selector = NEW_STRING;
    print(" TeX output ");
    print_int(year);
    print_char('.');
    print_two(month);
    print_char('.');
    print_two(day);
    print_char(':');
    print_two(time_ / 60);
    print_two(time_ % 60);
    selector = old_setting;
    dvi_out(cur_length);
    for(s = str_start[str_ptr]; s < pool_ptr; s++) {
        dvi_out(str_pool[s]);
    }
    pool_ptr = str_start[str_ptr]; // flush the current string
}
```
