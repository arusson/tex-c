# Section 1008

```c << Append an insertion to the current page and |goto contribute| >>=
if (page_contents == EMPTY) {
    freeze_page_specs(INSERTS_ONLY);
}
n = subtype(p);
r = PAGE_INS_HEAD;
while (n >= subtype(link(r))) {
    r = link(r);
}
if (subtype(r) != n) {
    // << Create a page insertion node with |subtype(r) = n|, and include the glue correction for box |n| in the current page state >>
}
if (type(r) == SPLIT_UP) {
    insert_penalties += float_cost(p);
}
else {
    last_ins_ptr(r) = p;
    delta = page_goal - page_total - page_depth + page_shrink;
    // this much room is left if we shrink the maximum
    if (count(n) == 1000) {
        h = height(p);
    }
    else {
        h = x_over_n(height(p), 1000)*count(n); // this much room is needed
    }
    if ((h <= 0 || h <= delta)
        && height(p) + height(r) <= dimen(n))
    {
        page_goal -= h;
        height(r) += height(p);
    }
    else {
        // << Find the best way to split the insertion, and change |type(r)| to |SPLIT_UP| >>
    }
}
goto contribute;
```
