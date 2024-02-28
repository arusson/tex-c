# Section 747

```c << Construct a vlist box for the fraction, according to |shift_up| and |shift_down| >>=
v = new_null_box();
type(v) = VLIST_NODE;
height(v) = shift_up + height(x);
depth(v) = depth(z) + shift_down;
width(v) = width(x); // this also equals |width(z)|
if (thickness(q) == 0) {
    p = new_kern((shift_up - depth(x)) - (height(z) - shift_down));
    link(p) = z;
}
else {
    y = fraction_rule(thickness(q));
    p = new_kern((axis_height(cur_size) - delta) - (height(z) - shift_down));
    link(y) = p;
    link(p) = z;
    p = new_kern((shift_up - depth(x)) - (axis_height(cur_size) + delta));
    link(p) = y;
}
link(x) = p;
list_ptr(v) = x;
```
