# Section 462

```c << Create a new glue specification whose width is |cur_val|; scan for its stretch and shrink components >>=
q = new_spec(ZERO_GLUE);
width(q) = cur_val;
if (scan_keyword("plus")) {
    scan_dimen(mu, true, false);
    stretch(q) = cur_val;
    stretch_order(q) = cur_order;
}
if (scan_keyword("minus")) {
    scan_dimen(mu, true, false);
    shrink(q) = cur_val;
    shrink_order(q) = cur_order;
}
cur_val = q;
```
