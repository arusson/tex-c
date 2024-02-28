# Section 748

```c << Put the fraction into a box with its delimiters, and make |new_hlist(q)| point to it >>=
if (cur_style < TEXT_STYLE) {
    delta = delim1(cur_size);
}
else {
    delta = delim2(cur_size);
}
x = var_delimiter(left_delimiter(q), cur_size, delta);
link(x) = v;
z = var_delimiter(right_delimiter(q), cur_size, delta);
link(v) = z;
new_hlist(q) = hpack(x, NATURAL);
```
