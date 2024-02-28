# Section 602

Here's a procedure that outputs a font definition.
Since $\TeX82$ uses at most 256 different fonts per job, *FNT_DEF1* is always used as the command code.

```c dvi.c
void dvi_font_def(internal_font_number f) {
    int k; // index into |str_pool|
    dvi_out(FNT_DEF1);
    dvi_out(f - FONT_BASE - 1);
    dvi_out(qqqq_b0(font_check[f]));
    dvi_out(qqqq_b1(font_check[f]));
    dvi_out(qqqq_b2(font_check[f]));
    dvi_out(qqqq_b3(font_check[f]));
    dvi_four(font_size[f]);
    dvi_four(font_dsize[f]);
    dvi_out(length(font_area[f]));
    dvi_out(length(font_name[f]));
    // << Output the font name whose internal number is |f| >>
}
```
