# Section 745

The numerator and denominator must be separated by a certain minimum clearance, called *clr* in the following program.
The difference between *clr* and the actual clearance is twice *delta*.

```c << Adjust |shift_up| and |shift_down| for the case of no fraction line >>=
if (cur_style < TEXT_STYLE) {
    clr = 7 * default_rule_thickness;
}
else {
    clr = 3 * default_rule_thickness;
}
delta = half(clr - ((shift_up - depth(x)) - (height(z) - shift_down)));
if (delta > 0) {
    shift_up += delta;
    shift_down += delta;
}
```
