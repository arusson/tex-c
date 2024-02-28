# Section 714

The width of an extensible character is the width of the repeatable module.
If this module does not have positive height plus depth, we don't use any copies of it, otherwise we use as few as possible (in groups of two if there is a middle part).

```c << Compute the minimum suitable height, |w|, and the corresponding number of extension steps, |n|; also set |width(b)| >>=
c = ext_rep(r);
u = height_plus_depth(f, c);
w = 0;
q = char_info(f, c);
width(b) = char_width(f, q) + char_italic(f, q);
c = ext_bot(r);
if (c != MIN_QUARTERWORD) {
    w += height_plus_depth(f, c);
}
c = ext_mid(r);
if (c != MIN_QUARTERWORD) {
    w += height_plus_depth(f, c);
}
c = ext_top(r);
if (c != MIN_QUARTERWORD) {
    w += height_plus_depth(f, c);
}
n = 0;
if (u > 0) {
    while (w < v) {
        w += u;
        incr(n);
        if (ext_mid(r) != MIN_QUARTERWORD) {
            w += u;
        }
    }
}
```
