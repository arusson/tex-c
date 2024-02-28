# Section 799

At the end of a row, we append an unset box to the current vlist (for `\halign`) or the current hlist (for `\valign`).
This unset box contains the unset boxes for the columns, separated by the tabskip glue.
Everything will be set later.

```c alignment.c
void fin_row() {
    pointer p; // the new unset box
    if (mode == -HMODE) {
        p = hpack(link(head), NATURAL);
        pop_nest();
        append_to_vlist(p);
        if (cur_head != cur_tail) {
            link(tail) = link(cur_head);
            tail = cur_tail;
        }
    }
    else {
        p = vpack(link(head), NATURAL);
        pop_nest();
        link(tail) = p;
        tail = p;
        space_factor = 1000;
    }
    type(p) = UNSET_NODE;
    glue_stretch(p) = 0;
    if (every_cr != null) {
        begin_token_list(every_cr, EVERY_CR_TEXT);
    }
    align_peek();
} // note that |glue_shrink(p) = 0| since |glue_shrink = shift_amount|
```
