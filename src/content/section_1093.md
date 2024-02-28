# Section 1093

```c builder/boxes_and_lists.c
void indent_in_hmode() {
    pointer p, q;
    if (cur_chr > 0) {
        // \indent
        p = new_null_box();
        width(p) = par_indent;
        if (abs(mode) == HMODE) {
            space_factor = 1000;
        }
        else {
            q = new_noad();
            math_type(nucleus(q)) = SUB_BOX;
            info(nucleus(q)) = p;
            p = q;
        }
        tail_append(p);
    }
}
```
