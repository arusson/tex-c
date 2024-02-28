# Section 793

```c << Lengthen the preamble periodically >>=
link(q) = new_null_box();
p = link(q); // a new alignrecord
info(p) = END_SPAN;
width(p) = NULL_FLAG;
cur_loop = link(cur_loop);
// << Copy the templates from node |cur_loop| into node |p| >>
cur_loop = link(cur_loop);
link(p) = new_glue(glue_ptr(cur_loop));
subtype(link(p)) = TAB_SKIP_CODE + 1;
```
