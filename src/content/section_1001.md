# Section 1001

```c << Initialize the current page, insert the \topskip glue ahead of |p|, and |goto continue| >>=
if (page_contents == EMPTY) {
    freeze_page_specs(BOX_THERE);
}
else {
    page_contents = BOX_THERE;
}
q = new_skip_param(TOP_SKIP_CODE); // now |temp_ptr = glue_ptr(q)|
if (width(temp_ptr) > height(p)) {
    width(temp_ptr) -= height(p);
}
else {
    width(temp_ptr) = 0;
}
link(q) = p;
link(CONTRIB_HEAD) = q;
goto continue_lbl;
```
