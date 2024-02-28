# Section 851

The remaining part of *try_break* deals with the calculation of demerits for a break from *r* to *cur_p*.

The first thing to do is calculate the badness, *b*.
This value will always be between zero and *INF_BAD +&nbsp;1*;
the latter value occurs only in the case of lines from *r* to *cur_p* that cannot shrink enough to fit the necessary width.
In such cases, node *r* will be deactivated.
We also deactivate node&nbsp;*r* when a break at&nbsp;*cur_p* is forced, since future breaks must go through a forced break.

```c << Consider the demerits for a line from |r| to |cur_p|; deactivate node |r| if it should no longer be active; then |goto continue| if a line from |r| to |cur_p| is infeasible, otherwise record a new feasible break >>=
artificial_demerits = false;
shortfall = line_width - cur_active_width[1]; // we're this much too short
if (shortfall > 0) {
    // << Set the value of |b| to the badness for stretching the line, and compute the corresponding |fit_class| >>
}
else{
    // << Set the value of |b| to the badness for shrinking the line, and compute the corresponding |fit_class| >>
}
if (b > INF_BAD || pi == EJECT_PENALTY) {
    // << Prepare to deactivate node |r|, and |goto deactivate| unless there is a reason to consider lines of text from |r| to |cur_p| >>
}
else {
    prev_r = r;
    if (b > threshold) {
        goto continue_lbl;
    }
    node_r_stays_active = true;
}
// << Record a new feasible break >>
if (node_r_stays_active) {
    goto continue_lbl; // |prev_r| has been set to |r|
}
deactivate:
// << Deactivate node |r| >>
```
