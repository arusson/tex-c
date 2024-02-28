# Section 757

When there is a subscript without a superscript, the top of the subscript should not exceed the baseline plus four-fifths of the x-height.

```c << Construct a subscript box |x| when there is no superscript >>=
x = clean_box(subscr(q), sub_style(cur_style));
width(x) += script_space;
if (shift_down < sub1(cur_size)) {
    shift_down = sub1(cur_size);
}
clr = height(x) - (abs(math_x_height(cur_size) * 4) / 5);
if (shift_down < clr) {
    shift_down = clr;
}
shift_amount(x) = shift_down;
```
