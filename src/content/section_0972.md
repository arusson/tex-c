# Section 972

A subtle point to be noted here is that the maximum depth&nbsp;*d* might be negative, so *cur_height* and *prev_dp* might need to be corrected even after a glue or kern node.

```c << If node |p| is a legal breakpoint, check if this break is the best known, and |goto done| if |p| is null or if the page-so-far is already too full to accept more stuff >>=
if (p == null) {
    pi = EJECT_PENALTY;
}
else {
    // << Use node |p| to update the current height and depth measurements; if this node is not a legal breakpoint, |goto not_found| or |update_heights|, otherwise set |pi| to the associated penalty at the break >>
}
// << Check if node |p| is a new champion breakpoint; then |goto done| if |p| is a forced break or if the page-so-far is already too full >>
if (type(p) < GLUE_NODE || type(p) > KERN_NODE) {
    goto not_found;
}

update_heights:
// << Update the current height and depth measurements with respect to a glue or kern node |p| >>

not_found:
if (prev_dp > d) {
    cur_height += prev_dp - d;
    prev_dp = d;
}
```
