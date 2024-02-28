# Section 758

The bottom of a superscript should never descend below the baseline plus one-fourth of the x-height.

```c << Construct a superscript box |x| >>=
x = clean_box(supscr(q), sup_style(cur_style));
width(x) += script_space;
if (odd(cur_style)) {
    clr = sup3(cur_size);
}
else if (cur_style < TEXT_STYLE) {
    clr = sup1(cur_size);
}
else {
    clr = sup2(cur_size);
}
if (shift_up < clr) {
    shift_up = clr;
}
clr = depth(x) + (abs(math_x_height(cur_size)) / 4);
if (shift_up < clr) {
    shift_up = clr;
}
```
