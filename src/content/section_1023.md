# Section 1023

The list of heldover insertions, running from *link(PAGE_HEAD)* to *page_tail*, must be moved to the contribution list when the user has specified no output routine.

```c << Perform the default output routine >>=
if (link(PAGE_HEAD) != null) {
    if (link(CONTRIB_HEAD) == null) {
        if (nest_ptr == 0) {
            tail = page_tail;
        }
        else {
            contrib_tail = page_tail;
        }
    }
    else {
        link(page_tail) = link(CONTRIB_HEAD);
    }
    link(CONTRIB_HEAD) = link(PAGE_HEAD);
    link(PAGE_HEAD) = null;
    page_tail = PAGE_HEAD;
}
ship_out(box(255));
box(255) = null;
```
