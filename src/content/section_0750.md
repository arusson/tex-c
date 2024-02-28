# Section 750

The following program builds a vlist box *v* for displayed limits.
The width of the box is not affected by the fact that the limits may be skewed.

```c << Construct a box with limits above and below it, skewed by |delta| >>=
x = clean_box(supscr(q), sup_style(cur_style));
y = clean_box(nucleus(q), cur_style);
z = clean_box(subscr(q), sub_style(cur_style));
v = new_null_box();
type(v) = VLIST_NODE;
width(v) = width(y);
if (width(x) > width(v)) {
    width(v) = width(x);
}
if (width(z) > width(v)) {
    width(v) = width(z);
}
x = rebox(x, width(v));
y = rebox(y, width(v));
z = rebox(z, width(v));
shift_amount(x) = half(delta);
shift_amount(z) = -shift_amount(x);
height(v) = height(y);
depth(v) = depth(y);
// << Attach the limits to |y| and adjust |height(v)|, |depth(v)| to account for their presence >>
new_hlist(q) = v;
```
