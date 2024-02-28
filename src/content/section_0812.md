# Section 812

We now have a completed alignment, in the list that starts at *head* and ends at *tail*.
This list will be merged with the one that encloses it.
(In case the enclosing mode is *MMODE*, for displayed formulas, we will need to insert glue before and after the display; that part of the program will be deferred until we're more familiar with such operations.)

In restricted horizontal mode, the *clang* part of *aux* is undefined;
an over-cautious Pascal runtime system may complain about this.

```c << Insert the current list into its environment >>=
aux_save = aux;
p = link(head);
q = tail;
pop_nest();
if (mode == MMODE) {
    // << Finish an alignment in a display >>
}
else {
    aux = aux_save;
    link(tail) = p;
    if (p != null) {
        tail = q;
    }
    if (mode == VMODE) {
        build_page();
    }
}
```
