# Section 1010

Here is the code that will split a long footnote between pages, in an emergency.
The current situation deserves to be recapitulated: Node *p* is an insertion into box *n*; the insertion will not fit, in its entirety, either because it would make the total contents of box *n* greater than `\dimen` *n*, or because it would make the incremental amount of growth *h* greater than the available space *delta*, or both.
(This amount *h* has been weighted by the insertion scaling factor, i.e., by `\count` *n* over 1000.)
Now we will choose the best way to break the vlist of the insertion, using the same criteria as in the `\vsplit` operation.

```c << Find the best way to split the insertion, and change |type(r)| to |SPLIT_UP| >>=
if (count(n) <= 0) {
    w = MAX_DIMEN;
}
else {
    w = page_goal - page_total - page_depth;
    if (count(n) != 1000) {
        w = x_over_n(w, count(n))*1000;
    }
}
if (w > dimen(n) - height(r)) {
    w = dimen(n) - height(r);
}
q = vert_break(ins_ptr(p), w, depth(p));
height(r) += best_height_plus_depth;

#ifdef STAT
if (tracing_pages > 0) {
    // << Display the insertion split cost >>
}
#endif

if (count(n) != 1000) {
  best_height_plus_depth = x_over_n(best_height_plus_depth, 1000)*count(n);
}
page_goal -= best_height_plus_depth;
type(r) = SPLIT_UP;
broken_ptr(r) = q;
broken_ins(r) = p;
if (q == null) {
    insert_penalties += EJECT_PENALTY;
}
else if (type(q) == PENALTY_NODE) {
    insert_penalties += penalty(q);
}
```
