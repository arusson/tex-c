# Section 1125

The kern nodes appended here must be distinguished from other kerns, lest they be wiped away by the hyphenation algorithm or by a previous line break.

The two kerns are computed with (machine-dependent) *real* arithmetic, but their sum is machine-independent; the net effect is machine-independent, because the user cannot remove these nodes nor access them via `\lastkern`.

```c << Append the accent with appropriate kerns, then set |p = q| >>=
t = slant(f) / 65536.0;
i = char_info(f, character(q));
w = char_width(f, i);
h = char_height(f, height_depth(i));
if (h != x) {
    // the accent must be shifted up or down
    p = hpack(p, NATURAL);
    shift_amount(p) = x - h;
}
delta = (scaled)round((w - a)/2.0 + h*t - x*s);
r = new_kern(delta);
subtype(r) = ACC_KERN;
link(tail) = r;
link(r) = p;
tail = new_kern(-a - delta);
subtype(tail) = ACC_KERN;
link(p) = tail;
p = q;
```
