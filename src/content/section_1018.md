# Section 1018

If many insertions are supposed to go into the same box, we want to know the position of the last node in that box, so that we don't need to waste time when linking further information into it.
The *last_ins_ptr* fields of the page insertion nodes are therefore used for this purpose during the packaging phase.

```c << Prepare all the boxes involved in insertions to act as queues >>=
r = link(PAGE_INS_HEAD);
while (r != PAGE_INS_HEAD) {
    if (best_ins_ptr(r) != null) {
        n = subtype(r);
        ensure_vbox(n);
        if (box(n) == null) {
            box(n) = new_null_box();
        }
        p = box(n) + LIST_OFFSET;
        while (link(p) != null) {
            p = link(p);
        }
        last_ins_ptr(r) = p;
    }
    r = link(r);
}
```
