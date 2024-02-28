# Section 1260

When the user gives a new identifier to a font that was previously loaded, the new name becomes the font identifier of record.
Font names '`xyz`' and '`XYZ`' are considered to be different.

```c << If this font has already been loaded, set |f| to the internal font number and |goto common_ending| >>=
flushable_string = str_ptr - 1;
for(f = FONT_BASE + 1; f <= font_ptr; f++) {
    if (str_eq_str(font_name[f], cur_name)
        && str_eq_str(font_area[f], cur_area))
    {
        if (cur_name == flushable_string) {
            flush_string;
            cur_name = font_name[f];
        }
        if (s > 0) {
            if (s == font_size[f]) {
                goto common_ending;
            }
        }
        else if (font_size[f] == xn_over_d(font_dsize[f], -s, 1000)) {
            goto common_ending;
        }
    }
}
```
