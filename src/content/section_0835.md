# Section 835

The first part of the following code is part of $\TeX$'s inner loop, so we don't want to waste any time.
The current active node, namely node *r*, contains the line number that will be considered next.
At the end of the list we have arranged the data structure so that *r = LAST_ACTIVE* and *line_number(LAST_ACTIVE)* $>$ *old_l*.

```c << If a line number class has ended, create new active nodes for the best feasible breaks in that class; then |return| if |r = LAST_ACTIVE|, otherwise compute the new |line_width| >>=
l = line_number(r);
if (l > old_l) {
    // now we are no longer in the inner loop
    if (minimum_demerits < AWFUL_BAD
        && (old_l != easy_line || r == LAST_ACTIVE))
    {
        // << Create new active nodes for the best feasible breaks just found >>
    }
    if (r == LAST_ACTIVE) {
        goto end;
    }
    // << Compute the new line width >>
}
```
