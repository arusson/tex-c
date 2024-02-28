# Section 746

In the case of a fraction line, the minimum clearance depends on the actual thickness of the line.

```c << Adjust |shift_up| and |shift_down| for the case of a fraction line >>=
if (cur_style < TEXT_STYLE) {
    clr = 3 * thickness(q);
}
else {
    clr = thickness(q);
}
delta = half(thickness(q));
delta1 = clr - ((shift_up - depth(x)) - (axis_height(cur_size) + delta));
delta2 = clr - ((axis_height(cur_size) - delta) - (height(z) - shift_down));
if (delta1 > 0) {
    shift_up += delta1;
}
if (delta2 > 0) {
    shift_down += delta2;
}
```
