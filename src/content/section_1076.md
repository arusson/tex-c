# Section 1076

The global variable *adjust_tail* will be non-null if and only if the current box might include adjustments that should be appended to the current vertical list.

```c << Append box |cur_box| to the current list, shifted by |box_context| >>=
if (cur_box != null) {
    shift_amount(cur_box) = box_context;
    if (abs(mode) == VMODE) {
        append_to_vlist(cur_box);
        if (adjust_tail != null) {
            if (ADJUST_HEAD != adjust_tail) {
                link(tail) = link(ADJUST_HEAD);
                tail = adjust_tail;
            }
            adjust_tail = null;
        }
        if (mode > 0) {
            build_page();
        }
    }
    else {
        if (abs(mode) == HMODE) {
            space_factor = 1000;
        }
        else {
            p = new_noad();
            math_type(nucleus(p)) = SUB_BOX;
            info(nucleus(p)) = cur_box;
            cur_box = p;
        }
        link(tail) = cur_box;
        tail = cur_box;
    }
}
```
