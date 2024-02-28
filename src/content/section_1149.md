# Section 1149

A displayed equation is considered to be three lines long, so we calculate the length and offset of line number *prev_graf* + 2.

```c << Calculate the length, |l|, and the shift amount, |s|, of the display lines >>=
if (par_shape_ptr == null) {
    if (hang_indent != 0) {
        if ((hang_after >= 0 && prev_graf + 2 > hang_after)
            || prev_graf + 1 < -hang_after)
        {
            l = hsize - abs(hang_indent);
            if (hang_indent > 0) {
                s = hang_indent;
            }
            else {
                s = 0;
            }
        }
    }
    else {
        l = hsize;
        s = 0;
    }
}
else {
    n = info(par_shape_ptr);
    if (prev_graf + 2 >= n) {
        p = par_shape_ptr + 2 * n;
    }
    else {
        p = par_shape_ptr + 2 * (prev_graf + 2);
    }
    s = mem[p - 1].sc;
    l = mem[p].sc;
}
```
