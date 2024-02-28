# Section 969

```c << Insert glue for |split_top_skip| and set |p = null| >>=
q = new_skip_param(SPLIT_TOP_SKIP_CODE);
link(prev_p) = q;
link(q) = p;
// now |temp_ptr = glue_ptr(q)|
if (width(temp_ptr) > height(p)) {
    width(temp_ptr) -= height(p);
}
else {
    width(temp_ptr) = 0;
}
p = null;
```
