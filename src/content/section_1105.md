# Section 1105

When *delete_last* is called, *cur_chr* is the *type* of node that will be deleted, if present.

```c builder/boxes_and_lists.c
void delete_last() {
    pointer p, q; // run through the current list
    int m;        // the length of a replacement list
    if (mode == VMODE && tail == head) {
        // << Apologize for inability to do the operation now, unless \unskip follows non-glue >>
    }
    else if (!is_char_node(tail) && type(tail) == cur_chr) {
        q = head;
        do {
            p = q;
            if (!is_char_node(q) && type(q) == DISC_NODE) {
                for(m = 1; m <= replace_count(q); m++) {
                    p = link(p);
                }
                if (p == tail) {
                    return;
                }
            }
            q = link(p);
        } while (q != tail);
        link(p) = null;
        flush_node_list(tail);
        tail = p;
    }
}
```
