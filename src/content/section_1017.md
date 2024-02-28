# Section 1017

When the following code is executed, the current page runs from node *link(PAGE_HEAD)* to node *prev_p*, and the nodes from *p* to *page_tail* are to be placed back at the front of the contribution list.
Furthermore the heldover insertions appear in a list from *link(HOLD_HEAD)* to *q*;
we will put them into the current page list for safekeeping while the user's output routine is active.
We might have *q = HOLD_HEAD*; and *p = null* if and only if *prev_p = page_tail*.
Error messages are suppressed within *vpackage*, since the box might appear to be overfull or underfull simply because the stretch and shrink from the `\skip` registers for inserts are not actually present in the box.

```c << Break the current page at node |p|, put it in box 255, and put the remaining nodes on the contribution list >>=
if (p != null) {
    if (link(CONTRIB_HEAD) == null) {
        if (nest_ptr == 0) {
            tail = page_tail;
        }
        else {
            contrib_tail = page_tail;
        }
    }
    link(page_tail) = link(CONTRIB_HEAD);
    link(CONTRIB_HEAD) = p;
    link(prev_p) = null;
}
save_vbadness = vbadness;
vbadness = INF_BAD;
save_vfuzz = vfuzz;
vfuzz = MAX_DIMEN; // inhibit error messages
box(255) = vpackage(link(PAGE_HEAD), best_size, EXACTLY, page_max_depth);
vbadness = save_vbadness;
vfuzz = save_vfuzz;
if (last_glue != MAX_HALFWORD) {
    delete_glue_ref(last_glue);
}
// this sets |last_glue = MAX_HALFWORD|:
// << Start a new current page >>
if (q != HOLD_HEAD) {
    link(PAGE_HEAD) = link(HOLD_HEAD);
    page_tail = q;
}
```
