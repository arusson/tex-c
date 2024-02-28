# Section 642

At the end of the program, we must finish things off by writing the postamble.
If *total_pages = 0*, the `DVI` file was never opened.
If *total_pages* $\geq$ *65536*, the `DVI` file will lie.
And if *max_push* $\geq$ *65536*, the user deserves whatever chaos might ensue.

An integer variable *k* will be declared for use by this routine.

```c << Finish the DVI file >>=
while (cur_s > -1) {
    if (cur_s > 0) {
        dvi_out(POP);
    }
    else {
        dvi_out(EOP);
        incr(total_pages);
    }
    decr(cur_s);
}
if (total_pages == 0) {
    print_nl("No pages of output.");
}
else {
    dvi_out(POST); // beginning of the postamble
    dvi_four(last_bop);
    last_bop = dvi_offset + dvi_ptr - 5; // |POST| location
    dvi_four(25400000);
    dvi_four(473628672); // conversion ratio for sp
    prepare_mag();
    dvi_four(mag); // magnification factor
    dvi_four(max_v);
    dvi_four(max_h);
    dvi_out(max_push / 256);
    dvi_out(max_push % 256);
    dvi_out((total_pages / 256) % 256);
    dvi_out(total_pages % 256);
    // << Output the font definitions for all fonts that were used >>
    dvi_out(POST_POST);
    dvi_four(last_bop);
    dvi_out(ID_BYTE);
    k = 4 + ((DVI_BUF_SIZE - dvi_ptr) % 4); // the number of 223's
    while (k > 0) {
        dvi_out(223);
        decr(k);
    }
    // << Empty the last bytes out of |dvi_buf| >>
    print_nl("Output written on ");
    slow_print(output_file_name);
    print(" (");
    print_int(total_pages);
    print(" page");
    if (total_pages != 1) {
        print_char('s');
    }
    print(", ");
    print_int(dvi_offset + dvi_ptr);
    print(" bytes).");
    b_close(dvi_file);
}
```
