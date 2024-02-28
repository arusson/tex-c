# Section 759

When both subscript and superscript are present, the subscript must be separated from the superscript by at least four times *default_rule_thickness*.
If this condition would be violated, the subscript moves down, after which both subscript and superscript move up so that the bottom of the superscript is at least as high as the baseline plus four-fifths of the x-height.

```c << Construct a sub/superscript combination box |x|, with the superscript offset by |delta| >>=
y = clean_box(subscr(q), sub_style(cur_style));
width(y) += script_space;
if (shift_down < sub2(cur_size)) {
    shift_down = sub2(cur_size);
}
clr = 4 * default_rule_thickness - ((shift_up - depth(x)) - (height(y) - shift_down));
if (clr > 0) {
    shift_down += clr;
    clr = (abs(math_x_height(cur_size) * 4) / 5) - (shift_up - depth(x));
    if (clr > 0) {
        shift_up += clr;
        shift_down -= clr;
    }
}
shift_amount(x) = delta; // superscript is |delta| to the right of the subscript
p = new_kern((shift_up - depth(x)) - (height(y) - shift_down));
link(x) = p;
link(p) = y;
x = vpack(x, NATURAL);
shift_amount(x) = shift_down;
```
